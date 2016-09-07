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
    int value = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            puzzle[x][y] = value++;
        }
    }
}

EightPuzzle::EightPuzzle(int val0, int val1, int val2,
                         int val3, int val4, int val5,
                         int val6, int val7, int val8 ) {

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

void EightPuzzle::getPuzzle(int matrix[][3]) {
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

void EightPuzzle::setPuzzle(int matrix[][3]) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            puzzle[x][y] = matrix[x][y];
        }
    }
}

void EightPuzzle::setPuzzle(int array[]) {
    int index = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            puzzle[x][y] = array[index++];
        }
    }
}


///////////////////////
//  Utility Methods  //
///////////////////////

void EightPuzzle::printPuzzle() {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            std::cout << puzzle[x][y] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
