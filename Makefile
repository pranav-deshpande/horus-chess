all:
	g++ -std=c++11 -g data.hpp move.hpp move.cpp chessboard.hpp chessboard.cpp initData.cpp	moveGen.cpp perft.cpp think.cpp main.cpp -o Horus
