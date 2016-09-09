//  Project:    8-Puzzle Search Solver
//  Assignment: CSCI 4350 Open Lab 1
//  Filename:   A* Search Puzzle Solver Driver Code (a_star.cpp)
//  Author:     Grayson M. Dubois

#include <iostream>
#include <set>
#include <cmath>

using namespace std;

// A puzzle is a 3x3 matrix containing the puzzle board
typedef int Puzzle[3][3];
// A Heuristic is a function that compares two puzzles
// and returns a value guessing the number of moves left
// to solve the puzzle
typedef int Heuristic(Puzzle&, Puzzle&);

// Function definitions for the different heuristics
Heuristic noHeuristic, displacedTiles, manhattan, myHeuristic;

// Function definitions
void getPuzzleFromInput(Puzzle&);
void printPuzzle(Puzzle&);

// The direction a move can take place
enum Direction {
    Up, Down, Left, Right
};

// A node in the search tree
struct Node {
    int id;
    int value;

    // Node initializer
    Node(int newID, int newValue) {
        id = newID;
        value = newValue;
    }

    // Overloaded < operator
    bool operator<(const Node& rhs) const{
        if (value < rhs.value) {
            return true;
        } else if (value == rhs.value && id < rhs.id) {
            return true;
        } else {
            return false;
        }
    }

    void print() const {
        cout << "Node - id=" << id << " val=" << value << "\n";
    }
};

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
    set<Node> closedList, openList, frontier;

    // Instantiate a universal node id number
    int globalID = 0;

    // Instantiate goal and puzzle
    Puzzle goal, puzzle;

    // Set up the goal puzzle board
    int value = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            goal[x][y] = value++;
        }
    }

    // Get the puzzle from standard input
    getPuzzleFromInput(puzzle);
    printPuzzle(puzzle);
    cout << "Heuristic result: " << heuristic(puzzle, goal) << "\n";

    return 0;
}

// No heuristic always returns 0 for the heuristic value.
// This causes the search to perform as a Uniform-Cost search.
int noHeuristic(Puzzle& p, Puzzle& g) {
    return 0;
}

// Displaced Tiles counts the numer of tiles (excluding the empty
// tile) that are not in their goal position
int displacedTiles(Puzzle& puzzle, Puzzle& goal) {
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
int manhattan(Puzzle& puzzle, Puzzle& goal) {
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
int myHeuristic(Puzzle& puzzle, Puzzle& goal) {
    const int averageSolutionCost = 22;
    if (depth <= averageSolutionCost) {
        return averageSolutionCost - depth;
    } else {
        return 0;
    }
}

// Get the contents of the puzzle from standard input
void getPuzzleFromInput(Puzzle& puzzle) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            cin >> puzzle[x][y];
        }
    }
}

// Print the contents of the puzzle to standard output
void printPuzzle(Puzzle& puzzle) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            cout << puzzle[x][y] << " ";
        }
        cout << "\n";
    }
}
