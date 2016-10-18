SRC_FILES = move.cpp chessboard.hpp chessboard.cpp initData.cpp moveGen.cpp perft.cpp think.cpp main.cpp

all: Horus_Debug Horus Horus_SuperFast

Horus_Debug: $(SRC_FILES)
	g++ -std=c++11 -g -O0 $(SRC_FILES) -o $@

Horus: $(SRC_FILES)
	g++ -DNDEBUG -std=c++11 -O3 -flto -fwhole-program $(SRC_FILES) -o $@
	
Horus_SuperFast: $(SRC_FILES)
	g++ -DNDEBUG -std=c++11 -Ofast -flto -fwhole-program -march=native -mtune=native $(SRC_FILES) -o $@

