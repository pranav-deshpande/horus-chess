all:
	g++ -std=c++11 -O3 -flto -fwhole-program data.hpp move.hpp move.cpp chessboard.hpp chessboard.cpp initData.cpp	moveGen.cpp perft.cpp think.cpp main.cpp -o Horus

