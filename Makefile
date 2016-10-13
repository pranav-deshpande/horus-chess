all:
	g++ -std=c++11 -pipe -O3 -flto move.cpp chessboard.cpp initData.cpp moveGen.cpp perft.cpp main.cpp -o Horus

