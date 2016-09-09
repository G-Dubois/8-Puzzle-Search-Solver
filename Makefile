all: EightPuzzle.cpp random_board.cpp a-star.cpp
	g++ -std=c++11 -g EightPuzzle.cpp random_board.cpp -o random_board.exe
	g++ -std=c++11 -g a-star.cpp -o a-star.exe
