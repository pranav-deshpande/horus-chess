all:
	g++ -std=c++11 -g data.hpp move.hpp move.cpp chessboard.hpp chessboard.cpp initHash.cpp moveGen.cpp perft.cpp main.cpp -o testEngine

