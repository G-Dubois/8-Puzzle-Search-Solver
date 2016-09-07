//  Project:    8-Puzzle Search Solver
//  Assignment: CSCI 4350 Open Lab 1
//  Filename:   Random Board Generator (random_board.cpp)
//  Author:     Grayson M. Dubois

#include <iostream>
#include "EightPuzzle.h"

////////////////////////////////
//  Constructors/Destructors  //
////////////////////////////////

EightPuzzle::EightPuzzle() {
    // Fill the puzzle board with values 0-8
    int value = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            puzzle[x][y] = value++;
        }
    }

    // Set the location of the empty space to [0, 0]
    empty = std::make_pair<int, int>(0, 0);
}

EightPuzzle::EightPuzzle(int val0, int val1, int val2,
                         int val3, int val4, int val5,
                         int val6, int val7, int val8 ) {

    // Fill the puzzle board with the integers given
    puzzle[0][0] = val0;
    puzzle[1][0] = val1;
    puzzle[2][0] = val2;
    puzzle[0][1] = val3;
    puzzle[1][1] = val4;
    puzzle[2][1] = val5;
    puzzle[0][2] = val6;
    puzzle[1][2] = val7;
    puzzle[2][2] = val8;
}

EightPuzzle::EightPuzzle(int array[]) {
    setPuzzle(array);
}

EightPuzzle::EightPuzzle(int matrix[][3]) {
    setPuzzle(matrix);
}

EightPuzzle::~EightPuzzle(){}


////////////////////////
//  Accessor Methods  //
////////////////////////

void EightPuzzle::getPuzzle(int array[]) {
    // Store the contents of the puzzle board in the array passed in
    int index = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            array[index++] = puzzle[x][y];
        }
    }
}

void EightPuzzle::getPuzzle(int matrix[][3]) {
    // Store the contents of the puzzle board in the matrix passed in
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            matrix[x][y] = puzzle[x][y];
        }
    }
}

int EightPuzzle::getValueAtLocation(int x, int y) {
    return puzzle[x][y];
}


///////////////////////
//  Mutator Methods  //
///////////////////////

void EightPuzzle::setPuzzle(int array[]) {
    int index = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            puzzle[x][y] = array[index++];
        }
    }
}

void EightPuzzle::setPuzzle(int matrix[][3]) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            puzzle[x][y] = matrix[x][y];
        }
    }
}


///////////////////////
//  Utility Methods  //
///////////////////////

void EightPuzzle::move(Direction direction) {
    switch (direction) {
    case Up:
        // Move 1 space up if not at the top
        if (canMove(Up)) {
            std::pair<int, int> up(empty.first, empty.second - 1);
            swap(empty, up);
            empty = up;
        }
        break;
    case Down:
        // Move 1 space down if not at the bottom
        if (canMove(Down)) {
            std::pair<int, int> down(empty.first, empty.second + 1);
            swap(empty, down);
            empty = down;
        }
        break;
    case Left:
        // Move 1 space left if not at the left edge
        if (canMove(Left)) {
            std::pair<int, int> left(empty.first - 1, empty.second);
            swap(empty, left);
            empty = left;
        }
        break;
    case Right:
        // Move 1 space right if not at the right edge
        if (canMove(Right)) {
            std::pair<int, int> right(empty.first + 1, empty.second);
            swap(empty, right);
            empty = right;
        }
        break;
    }
}

// Determine if the empty space can be moved in the given direction
bool EightPuzzle::canMove(Direction direction) {
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
        break;
    default:
        return false;
    }
}

void EightPuzzle::printPuzzle() {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            std::cout << puzzle[x][y] << " ";
        }
        std::cout << "\n";
    }
}


/////////////////////
// Helper Methods  //
/////////////////////

// Swap two items on the puzzle board
void EightPuzzle::swap(std::pair<int, int> loc1, std::pair<int, int> loc2) {
    int temp = puzzle[loc1.first][loc1.second];
    puzzle[loc1.first][loc1.second] = puzzle[loc2.first][loc2.second];
    puzzle[loc2.first][loc2.second] = temp;
}
