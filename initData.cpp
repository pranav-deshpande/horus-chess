#include "chessboard.hpp"

// Data Definitions - Some of these variables are required globally
int8_t board64[] = {
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
};

int8_t board120[] = {
	OB, OB, OB, OB, OB, OB, OB, OB, OB, OB,
	OB, OB, OB, OB, OB, OB, OB, OB, OB, OB,
	OB,  0,  1,  2,  3,  4,  5,  6,  7, OB,
	OB,  8,  9, 10, 11, 12, 13, 14, 15, OB,
	OB, 16, 17, 18, 19, 20, 21, 22, 23, OB,
	OB, 24, 25, 26, 27, 28, 29, 30, 31, OB,
	OB, 32, 33, 34, 35, 36, 37, 38, 39, OB,
	OB, 40, 41, 42, 43, 44, 45, 46, 47, OB,
	OB, 48, 49, 50, 51, 52, 53, 54, 55, OB,
	OB, 56, 57, 58, 59, 60, 61, 62, 63, OB,
	OB, OB, OB, OB, OB, OB, OB, OB, OB, OB,
	OB, OB, OB, OB, OB, OB, OB, OB, OB, OB
};

char pieceChars[] = {'.', 'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k'};

unordered_map<char, int> reversePieceChars;
string squareMapping[64];
unordered_map<string, int> reverseSquareMapping;

ULL chessboard::hashList[13][64];
ULL chessboard::sideHash[2];
ULL chessboard::whiteCastleHash[2];
ULL chessboard::blackCastleHash[2];
ULL chessboard::enPassantHash[64];

void setUpDebugging() {

	// Required for printing things to the console etc.
	for(int i = 0; i < 13; i++) {
		reversePieceChars[ pieceChars[i] ] = i;
	}

	string temp;
	int k = 0;
	for(int i = '1'; i <= '8'; i++) {
		for(int j = 'a'; j <= 'h'; j++) {
			temp = string(1, j) + string(1, i);
			squareMapping[k++] = temp;
		}
	}	

	for(int i = 0; i < 64; i++) {
		reverseSquareMapping[ squareMapping[i] ] = i;
	}

}

void initHash() {
	
	// Intitialize the hash lists
	for(int square = 0; square < 64; square++) {
		chessboard::hashList[0][square] = 0;
	}
	
	for(int piece = wp; piece <= bk; piece++ ) {
		for(int square = 0; square < 64; square++) {
			chessboard::hashList[piece][square] = rand();
		}
	}
	
	for(int i = 0; i < 2; i++) {
		chessboard::whiteCastleHash[i] = rand();
		chessboard::blackCastleHash[i] = rand();
	}
	
	chessboard::sideHash[black] = rand();
	chessboard::sideHash[white] = rand();
	
	for(int square = 0; square < 64; square++) {
		chessboard::enPassantHash[square] = rand();
	} 
}

void raiseAssertionFailure(char const * msg, char const * file, int line)
{
	static bool alreadyCalled = false;
	if (alreadyCalled) return;
	alreadyCalled = true;

	cerr << "### ASSERTION FAILED: \"" << msg << "\" (" << file << ", line " << line << ")" << endl;
	flush(cerr);
	dumpAll();
	abort();
}

