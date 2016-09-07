//  Project:    8-Puzzle Search Solver
//  Assignment: CSCI 4350 Open Lab 1
//  Filename:   Random Board Generator (random_board.cpp)
//  Author:     Grayson M. Dubois

#include <iostream>
#include <random>

#include "EightPuzzle.h"
using namespace std;

default_random_engine re;

// Maps the contents of an array to a 3x3 matrix
void map(int array[], int matrix[][3]) {
    int index = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            matrix[x][y] = array[index++];
        }
    }
}

// Reads the contents of a matrix from standard input
void readContents(int array[]) {
    for (int i = 0; i < 9; i++) {
        cin >> array[i];
    }
}

int main (int argc, char* argv[]) {

    int moves;

    if (argc < 3) {
        cerr << "ERROR: Too few command line arguments; Need 2: seed & number of random moves to make\n";
        return 1;
    } else {
        re.seed(atoi(argv[1]));
        moves = atoi(argv[2]);
    }

    // Get the contents of the puzzle from standard input
    int contents[9];
    readContents(contents);

    // Initialize the puzzle with the contents read in from stdin
    EightPuzzle puzzle(contents);
    //puzzle.printPuzzle();

    return 0;
}
