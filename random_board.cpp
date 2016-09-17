//  Project:    8-Puzzle Search Solver
//  Assignment: CSCI 4350 Open Lab 1
//  Filename:   Random Board Generator (random_board.cpp)
//  Author:     Grayson M. Dubois

#include <iostream>
#include <random>

using namespace std;


typedef int EightPuzzle[3][3];

enum Direction {
    Up, Down, Left, Right
};


void readContents(EightPuzzle&);
Direction randomMovement(EightPuzzle& puzzle);
void move(EightPuzzle&, Direction);
bool canMove(EightPuzzle&, Direction);
void swap(EightPuzzle&, pair<int, int>, pair<int, int>);
void print(EightPuzzle&);


pair<int, int> empty(0, 0);

int main (int argc, char* argv[]) {

    int moves;

    if (argc < 3) {
        cerr << "ERROR: Too few command line arguments; Need 2: seed & number of random moves to make\n";
        return 1;
    } else {
        srandom(atoi(argv[1]));
        moves = atoi(argv[2]);
    }


    // Initialize the puzzle with the contents read in from stdin
    EightPuzzle puzzle;
    readContents(puzzle);

    // Make moves number of random movements
    for (int i = 0; i < moves; i++) {
        move(puzzle, randomMovement(puzzle));
    }

    // Print the contents of the puzzle
    print(puzzle);


    return 0;
}

// Reads the contents of a matrix from standard input
void readContents(EightPuzzle& puzzle) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            cin >> puzzle[x][y];
        }
    }
}

Direction randomMovement(EightPuzzle& puzzle) {
    Direction direction = Up;
    do {
        direction = static_cast<Direction>((4.0*random()) / (RAND_MAX + 1.0));
    } while(!canMove(puzzle, direction));

    return direction;
}

void move(EightPuzzle& puzzle, Direction direction) {
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


void print(EightPuzzle& puzzle) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            std::cout << puzzle[x][y] << " ";
        }
        std::cout << "\n";
    }
}
