//  Project:    8-Puzzle Search Solver
//  Assignment: CSCI 4350 Open Lab 1
//  Filename:   Random Board Generator (random_board.cpp)
//  Author:     Grayson M. Dubois

enum Movement{
    Up, Down, Left, Right
};

class EightPuzzle {
private:
    int puzzle[3][3];       // The puzzle array stores the contents of the puzzle board

public:

    ////////////////////////////////
    //  Constructors/Destructors  //
    ////////////////////////////////

    EightPuzzle();                  // Default Constructor

    EightPuzzle(int, int, int,      // Initializing constructor which takes 9 ints
                int, int, int,      // as arguments to fill the puzzle matrix
                int, int, int);

    EightPuzzle(int[]);            // Initializing constructor which takes an
                                    // array of ints to fill the puzzle matrix

    EightPuzzle(int[][3]);          // Initializing constructor which takes a 2d
                                    // array of ints to fill the puzzle matrix

    ~EightPuzzle();                 // Default Destructor


    ////////////////////////
    //  Accessor Methods  //
    ////////////////////////

    void getPuzzle(int[][3]);       // Stores the contents of the puzzle in the
                                    // array passed to the function

    int getValueAtLocation(int, int);       // Returns the contents of the puzzle at the
                                            // given indices

    ///////////////////////
    //  Mutator Methods  //
    ///////////////////////

    void setPuzzle(int[][3]);       // Set the contents of the puzzle with the
                                    // array passed to the function

    void setPuzzle(int[]);          // Set the contents of the puzzle with the
                                    // array passed to the function


    ///////////////////////
    //  Utility Methods  //
    ///////////////////////

    //void move
    void printPuzzle();

};
