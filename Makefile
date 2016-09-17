all: random_board a-star

random_board: random_board.cpp
	g++ -std=c++11 -g random_board.cpp -o random_board.exe

a-star: a-star.cpp
	g++ -std=c++11 -g a-star.cpp -o a-star.exe
