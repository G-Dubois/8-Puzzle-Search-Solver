//  Project:    8-Puzzle Search Solver
//  Assignment: CSCI 4350 Open Lab 1
//  Filename:   A* Search Puzzle Solver Driver Code (a-star.cpp)
//  Author:     Grayson M. Dubois

#include <iostream>
#include <set>
#include <cmath>
#include <vector>

using namespace std;

// A puzzle is a 3x3 matrix containing the puzzle board
typedef int EightPuzzle[3][3];
// A Heuristic is a function that compares two puzzles
// and returns a value guessing the number of moves left
// to solve the puzzle
typedef int Heuristic(EightPuzzle&);

// Function definitions for the different heuristics
Heuristic noHeuristic, displacedTiles, manhattan, myHeuristic;

// The direction a move can take place
enum Direction {
    Up, Down, Left, Right
};

// A node in the search tree
struct Node {
    int id;
    int gValue;
    int hValue;
    int fValue;
    int depth;

    EightPuzzle puzzle;
    Node* parent;
    set<Node*> children;

    int value() {
        return (gValue + hValue);
    }

    // Node initializer
    Node(int newID, int gVal, int hVal, EightPuzzle& puz, Node* par) {
        id = newID;
        gValue = gVal;
        hValue = hVal;
        fValue = gValue + hValue;

        // Assigning the puzzle
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                puzzle[x][y] = puz[x][y];
            }
        }

        parent = par;
        if (parent != nullptr) {
            depth = par->depth + 1;
        } else {
            depth = 0;
        }
    }

    // Initializer for closed list node
    Node(EightPuzzle& puz) {
        id = gValue = hValue = 0;
        parent = nullptr;
        children.empty();
        
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                puzzle[x][y] = puz[x][y];
            }
        }
    }

    // Overloaded < operator
    bool operator<(const Node& rhs) const{
        if (fValue < rhs.fValue) {
            return true;
        } else if (fValue == rhs.fValue && id > rhs.id) {
            return true;
        } else {
            return false;
        }
    }

    void print(){
        cout << "Node - id=" << id << " val=" << value() << "\n";
    }
};

struct NodePtrCmp {
    bool operator()(const Node* lhs, const Node* rhs) const{  
        if (lhs->fValue < rhs->fValue) {
            return true;
        } else if (lhs->fValue == rhs->fValue && lhs->id > rhs->id) {
            return true;
        } else {
            return false;
        }
    }
};

ostream& operator<< (ostream& out, Node& node) {
    out << "{id=" << node.id << "; f(s)=" << node.value() << "}";
    return out;
}

// Function definitions
void getPuzzleFromInput(EightPuzzle&);
void print(EightPuzzle&);
void printFrontier(set<Node*>&);
void successor(Node*);
bool canMove(EightPuzzle&, Direction);
bool isGoal(EightPuzzle&);
void move(EightPuzzle&, Direction);
void swap(EightPuzzle&, pair<int, int>, pair<int, int>);
bool isInSet(EightPuzzle&, set<Node*>);

// The depth and goal are made global because they are used in heuristic function
int globalID;
int depth = 0;                          // The total depth of the path
int V = 0;                              // The number of nodes expanded
int N = 0;                              // The closed list and open list size
EightPuzzle goal;
Heuristic* heuristic;

int main (int argc, char* argv[]) {

    // Get the heuristic number from the command line arguments
    int heuristicNumber = 0;
    if (argc < 2) {
        cerr << "ERROR: Too few command line arguments; Need 1 for seed \n";
    } else {
        heuristicNumber = atoi(argv[1]);
    }

    // Set up the heuristic to use
    heuristic = &noHeuristic;
    switch (heuristicNumber) {
    case 1:
        heuristic = &displacedTiles;
        break;
    case 2:
        heuristic = &manhattan;
        break;
    case 3:
        heuristic = &myHeuristic;
        break;
    }


    // Instantiate the closed and open lists, and frontier
    set<Node*> closedList;
    set<Node*, NodePtrCmp> openList, frontier, solution;

    // Instantiate puzzle
    EightPuzzle puzzle;

    // Set up the goal puzzle board
    int value = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            goal[x][y] = value++;
        }
    }

    // Get the puzzle from standard input
    getPuzzleFromInput(puzzle);

    //print(puzzle);
    //print(puzzle);
    //cout << "Heuristic result: " << heuristic(puzzle, goal) << "\n";

    // Set a universal node id number and initial depth
    globalID = 0;
    depth = 0;
    Node* head = new Node(++globalID, depth, heuristic(puzzle), puzzle, nullptr);

    frontier.insert(head);

    // Now we are ready to run the search

    bool done = false;
    while (!done) {
    
        // Pop the first element off of the frontier
        Node* expandedNode = *frontier.begin();
        frontier.erase(frontier.begin());

        //print(expandedNode->puzzle);
        //cout << "\n";

        // Clear the remaining frontier into the open list
        openList.clear();
        openList.insert(frontier.begin(), frontier.end());
        frontier.clear();

        // Insert the current node into the open list
        if (!isInSet(expandedNode->puzzle, closedList)) {
            closedList.insert(new Node(expandedNode->puzzle));
        }

        //printf("Closed List contains %i states\n", int(closedList.size()));
        //for (set<Node*>::iterator iter = closedList.begin();
        //     iter != closedList.end(); iter++) {
        //    print((*iter)->puzzle);
        //    cout << "\n";
        //}

        if ( isGoal(expandedNode->puzzle) ) {
            done = true;
        }

        if (!done) {
            // Calling the successor function is the equivalent of expanding the node.
            // We find all children of the node being expanded.
            successor(expandedNode);

            //cout << "Parent:\n";
            //print(expandedNode->puzzle);
            //cout << "Children:\n";

            // We insert all the children into the frontier, and then reinsert the
            // nodes in the open list to the frontier.
            // But first, we need to remove any nodes with states we have already explored.
            for (set<Node*>::iterator iter = expandedNode->children.begin();
                 iter != expandedNode->children.end(); iter++) {

                //print((*iter)->puzzle);
                //cout << "\n";
                
                if (isInSet((*iter)->puzzle, closedList)) {
                    expandedNode->children.erase(*iter);
                    delete (*iter);
                    //cout << "Found a state in the closed list\n";
                }
            }
            frontier.insert(expandedNode->children.begin(), expandedNode->children.end());
        }
    
        frontier.insert(openList.begin(), openList.end());


        //printf("Frontier Contains:\n");
        //for (Node* np : frontier) {
        //    cout << "\t" << *np << "\n";
        //}

        V++;
        N = closedList.size() + frontier.size();
        depth = expandedNode->depth;

        //printf("Visited so far: %i\n", V);
        //printf("Nodes in memory: %i\n", N);
        //printf("Depth of best path so far: %i\n", depth);

        if (done) {
            cout << "Solution:\n";
            print(expandedNode->puzzle);
            cout << "\n";
        }

        
    }

    double branchingFactor = pow(N, 1.0/depth);
    
    cout << "V=" << V << "\n";
    cout << "N=" << N << "\n";
    cout << "d=" << depth << "\n";
    printf("b=%f\n", branchingFactor);
    

    return 0;
}

// No heuristic always returns 0 for the heuristic value.
// This causes the search to perform as a Uniform-Cost search.
int noHeuristic(EightPuzzle& _) {
    return 0;
}

// Displaced Tiles counts the numer of tiles (excluding the empty
// tile) that are not in their goal position
int displacedTiles(EightPuzzle& puzzle) {
    int numberOfDisplacedTiles = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (puzzle[x][y] != 0 && puzzle[x][y] != goal[x][y]) {
                numberOfDisplacedTiles++;
            }
        }
    }
    return numberOfDisplacedTiles;
}

// Manhattan counts the distance each tile is from its goal location
// and sums these together.
int manhattan(EightPuzzle& puzzle) {
    int totalDistanceOfDisplacedTiles = 0;
    //cout << "h2 = ";
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            int done = 0;
            if (puzzle[x][y] != 0) {
                for (int j = 0; done == 0 && j < 3; j++) {
                    for (int i = 0; i < 3; i++) {
                        if (goal[i][j] == puzzle[x][y] ) {
                            totalDistanceOfDisplacedTiles += abs(x - i) + abs(y - j);
                            //cout << abs(x - i) + abs(y - j) << " + ";
                            done = 1;
                            break;
                        }
                    }
                }
            }
        }
    }
    return totalDistanceOfDisplacedTiles;
}

// In my heuristic, I subtract the current tree depth from the
// average solution cost of solving the 8-puzzle, which is 22.
// If the depth has surpassed the average solution cost, return
// 0, rather than a negative value
int myHeuristic(EightPuzzle& puzzle) {
    const int averageSolutionCost = 22;
    if (depth <= averageSolutionCost) {
        //printf("My Heuristic result: %i\n", averageSolutionCost - depth);
        return averageSolutionCost - depth;
    } else {
        //printf("My Heuristic result: 0\n");
        return 0;
    }
}

// Get the contents of the puzzle from standard input
void getPuzzleFromInput(EightPuzzle& puzzle) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            cin >> puzzle[x][y];
        }
    }
}

// Print the contents of the puzzle to standard output
void print(EightPuzzle& puzzle) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            cout << puzzle[x][y] << " ";
        }
        cout << "\n";
    }
}

// Print the contents of the frontier
void printFrontier(set<Node*>& frontier) {
    cout << "Frontier: ";
    for (Node* nodePtr : frontier) {
        cout << *nodePtr << ", ";
    }
    cout << "\n";
}

// Successor function determines the next possible states to explore
void successor(Node* node) {
    set<Node*> successiveNodes;
    for (int dir = Up; dir < Right + 1; dir++) {
        Direction direction = static_cast<Direction>(dir);
        if (canMove(node->puzzle, direction)) {
            EightPuzzle newPuzzle;
            for (int y = 0; y < 3; y++) {
                for (int x = 0; x < 3; x++) {
                    newPuzzle[x][y] = node->puzzle[x][y];
                }
            }
            move(newPuzzle, direction);
            //cout << "Moving (" << direction << ")\n";
            node->children.insert(new Node(globalID++, node->gValue + 1, heuristic(newPuzzle), newPuzzle, node));
        }
    }
}

// Check to see if a puzzle exists in a set of nodes
bool isInSet(EightPuzzle& puzzle, set<Node*> nodeSet) {

    //cout << "Puzzle in question:\n";
    //print(puzzle);
    //cout << "\nClosed List:\n";
    bool isInSet = false;

    for (set<Node*>::iterator iter = nodeSet.begin();
         iter != nodeSet.end(); iter++) {

        //print((*iter)->puzzle);
        //cout << "\n";
        bool isSame = true;
        
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                if (puzzle[x][y] != (*iter)->puzzle[x][y]) {
                    isSame = false;
                }
            }
        }
        if (isSame) {
            return true;
        }
    }
    return false;
}

// Check to see if the puzzle is in the goal state
bool isGoal(EightPuzzle& puzzle) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (puzzle[x][y] != goal[x][y]) {
                return false;
            }
        }
    }
    return true;
}


void move(EightPuzzle& puzzle, Direction direction) {
    pair<int, int> empty;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (puzzle[x][y] == 0) {
                empty = make_pair(x ,y);
            }
        }
    }

    switch (direction) {
    case Up:
        // Move 1 space up if not at the top
        if (canMove(puzzle, Up)) {
            pair<int, int> up(empty.first, empty.second - 1);
            swap(puzzle, empty, up);
            empty = up;
        }
        break;
    case Down:
        // Move 1 space down if not at the bottom
        if (canMove(puzzle, Down)) {
            pair<int, int> down(empty.first, empty.second + 1);
            swap(puzzle, empty, down);
            empty = down;
        }
        break;
    case Left:
        // Move 1 space left if not at the left edge
        if (canMove(puzzle, Left)) {
            pair<int, int> left(empty.first - 1, empty.second);
            swap(puzzle, empty, left);
            empty = left;
        }
        break;
    case Right:
        // Move 1 space right if not at the right edge
        if (canMove(puzzle, Right)) {
            pair<int, int> right(empty.first + 1, empty.second);
            swap(puzzle, empty, right);
            empty = right;
        }
        break;
    }
}

bool canMove(EightPuzzle& puzzle, Direction direction) {
    pair<int, int> empty;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (puzzle[x][y] == 0) {
                empty = make_pair(x ,y);
            }
        }
    }

    switch (direction) {
    case Up:
        if (empty.second > 0) {
            return true;
        }
        break;
    case Down:
        if (empty.second < 2) {
            return true;
        }
        break;
    case Left:
        if (empty.first > 0) {
            return true;
        }
        break;
    case Right:
        if (empty.first < 2) {
            return true;
        }
    default:
        return false;
    }
}

void swap(EightPuzzle& puzzle, pair<int, int> loc1, pair<int, int> loc2) {
    int temp = puzzle[loc1.first][loc1.second];
    puzzle[loc1.first][loc1.second] = puzzle[loc2.first][loc2.second];
    puzzle[loc2.first][loc2.second] = temp;
}
