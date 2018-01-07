CXX=g++

CFLAGS=-I -std=c++11 -Wall -pipe
CFLAGS_Debug=$(CFLAGS) -g -O0
CFLAGS_Release=$(CFLAGS) -DNDEBUG -O3 -flto -fwhole-program
CFLAGS_SuperFast=$(CFLAGS) -DNDEBUG -Ofast -flto -fwhole-program -march=native -mtune=native

SRC_FILES = move.cpp chessboard.cpp initData.cpp moveGen.cpp perft.cpp think.cpp main.cpp

all: Horus_Debug Horus Horus_SuperFast

Horus_Debug: $(SRC_FILES)
	$(CXX) $(CFLAGS_Debug) $(SRC_FILES) -o $@

Horus: $(SRC_FILES)
	$(CXX) $(CFLAGS_Release) $(SRC_FILES) -o $@

Horus_SuperFast: $(SRC_FILES)
	$(CXX) $(CFLAGS_SuperFast) $(SRC_FILES) -o $@

clean:
	rm Horus_Debug Horus_SuperFast
