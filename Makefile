CXX=g++

CFLAGS=-I -std=c++11 -Wall -pipe
CFLAGS_Debug=$(CFLAGS) -g -O0
CFLAGS_Release=$(CFLAGS) -DNDEBUG -O3 -flto -fwhole-program
CFLAGS_SuperFast=$(CFLAGS) -DNDEBUG -Ofast -flto -fwhole-program -march=native -mtune=native

SRC_FILES = src/move.cpp src/chessboard.cpp src/initData.cpp src/moveGen.cpp src/perft.cpp src/think.cpp src/main.cpp

all: Horus_Debug Horus Horus_SuperFast

Horus_Debug: $(SRC_FILES)
	$(CXX) $(CFLAGS_Debug) $(SRC_FILES) -o exec/$@

Horus: $(SRC_FILES)
	$(CXX) $(CFLAGS_Release) $(SRC_FILES) -o exec/$@
	cp exec/$@ ./$@

Horus_SuperFast: $(SRC_FILES)
	$(CXX) $(CFLAGS_SuperFast) $(SRC_FILES) -o exec/$@

install:
	cp ./Horus /usr/games/Horus

clean:
	rm exec/Horus_Debug exec/Horus_SuperFast exec/Horus ./Horus
