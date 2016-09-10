//  Project:    8-Puzzle Search Solver
//  Assignment: CSCI 4350 Open Lab 1
//  Filename:   A* Search Puzzle Solver Driver Code (a_star.cpp)
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
typedef int Heuristic(EightPuzzle&, EightPuzzle&);

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

    EightPuzzle puzzle;
    Node* parent;
    vector<Node*> children;

    int value() {
        return (gValue + hValue);
    }

    // Node initializer
    Node(int newID, int gVal, int hVal, EightPuzzle& puz, Node* par) {
        id = newID;
        gValue = gVal;
        hValue = hVal;

        // Assigning the puzzle
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                puzzle[x][y] = puz[x][y];
            }
        }

        parent = par;
    }

    // Overloaded < operator
    bool operator<(Node& rhs){
        if (this->value() < rhs.value()) {
            return true;
        } else if (value() == rhs.value() && id < rhs.id) {
            return true;
        } else {
            return false;
        }
    }

    void print(){
        cout << "Node - id=" << id << " val=" << value() << "\n";
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

// The depth is made global because it is used in my heuristicNumber
int depth = 0;

int main (int argc, char* argv[]) {

    // Get the heuristic number from the command line arguments
    int heuristicNumber = 0;
    if (argc < 2) {
        cerr << "ERROR: Too few command line arguments; Need 1 for seed \n";
    } else {
        heuristicNumber = atoi(argv[1]);
    }

    // Set up the heuristic to use
    Heuristic* heuristic = &noHeuristic;
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
    set<Node*> closedList, openList, frontier;

    // Instantiate goal and puzzle
    EightPuzzle goal, puzzle;

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
    //cout << "Heuristic result: " << heuristic(puzzle, goal) << "\n";

    // Instantiate a universal node id number and initial depth
    int globalID = 0;
    depth = 0;
    Node* head = new Node(++globalID, depth, heuristic(puzzle, goal), puzzle, nullptr);

    frontier.insert(head);
    printFrontier(frontier);

    // Now we are ready to run the search


    return 0;
}

// No heuristic always returns 0 for the heuristic value.
// This causes the search to perform as a Uniform-Cost search.
int noHeuristic(EightPuzzle& p, EightPuzzle& g) {
    return 0;
}

// Displaced Tiles counts the numer of tiles (excluding the empty
// tile) that are not in their goal position
int displacedTiles(EightPuzzle& puzzle, EightPuzzle& goal) {
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
int manhattan(EightPuzzle& puzzle, EightPuzzle& goal) {
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
int myHeuristic(EightPuzzle& puzzle, EightPuzzle& goal) {
    const int averageSolutionCost = 22;
    if (depth <= averageSolutionCost) {
        return averageSolutionCost - depth;
    } else {
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


// Check to see if the puzzle is in the goal state
bool isGoal(EightPuzzle& puzzle, EightPuzzle& goal) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (puzzle[x][y] != goal[x][y]) {
                return false;
            }
        }
    }
    return true;
}
