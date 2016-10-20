// file data.hpp - contains several macros, enums and other important include files etc.

#ifndef __DATA__
#define __DATA__

// standard headers required
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
#include <climits>
#include <vector>
#include <cstdlib>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <chrono>

using namespace std;
typedef unsigned long long ULL;

#define BOARDSIZE 120

// off-board and empty squares
#define OB -1
#define EM 0

// Engine Side required for GUI mode
#define empty -1

// For search
#define infinity 1000000

// black = 0, white = 1
enum {
	black, white
};

// Assigning values to identify the pieces
enum {
	wp = 1, wn, wb, wr, wq, wk,
	bp, bn, bb, br, bq, bk
};

// Labelling the files and ranks
enum {
	fileA = 1, fileB, fileC, fileD, fileE, fileF, fileG, fileH,
	rank1 = 1, rank2, rank3, rank4, rank5, rank6, rank7, rank8
};

// Labelling the squares
enum {
	a1 = 21, b1, c1, d1, e1, f1, g1, h1,
  	a2 = 31, b2, c2, d2, e2, f2, g2, h2,
  	a3 = 41, b3, c3, d3, e3, f3, g3, h3,
  	a4 = 51, b4, c4, d4, e4, f4, g4, h4,
    a5 = 61, b5, c5, d5, e5, f5, g5, h5,
	a6 = 71, b6, c6, d6, e6, f6, g6, h6,
	a7 = 81, b7, c7, d7, e7, f7, g7, h7,
	a8 = 91, b8, c8, d8, e8, f8, g8, h8
};

// This helps us to detect various types of draws and also checkmate
enum EndOfGameReason {
	 NoEndOfGame = 0, Mate, Stalemate, FiftyMoveRule, ThreeFoldRepetition, InsufficientMaterial
};

// Directions
#define UP 10
#define DOWN -10
#define RIGHT 1
#define LEFT -1
#define TOP_LEFT 9
#define TOP_RIGHT 11
#define BOTTOM_LEFT -11
#define BOTTOM_RIGHT -9

// Knight moves
#define NM1 8
#define NM2 -8
#define NM3 12
#define NM4 -12
#define NM5 19
#define NM6 -19
#define NM7 21
#define NM8 -21
 
// Declaration of some data and functions

// Required for indexing purposes - Square Lookup
extern int board64[64];
extern int board120[120];

// Printing the pieces and parsing moves(especially the promoted piece)
extern char pieceChars[13];
extern unordered_map<char, int> reversePieceChars;

// Printing moves and parsing moves
extern string squareMapping[64];
extern unordered_map<string, int> reverseSquareMapping;

// Functions required for initializing certain data
extern void setUpDebugging();
extern void initHash();

// Performance testing to test the correctness of the chessboard::generateAllMoves() function
extern void runPerftTests();

// Used for debugging the move generating function if something gets caught while we run perft tests
// Helps in tracing at which position the move generating function made a mistake
extern void debugPerft(string &test, int depth);

// Run sample perft test
extern void samplePerftTest();

inline bool isValidSquare(int sq) {
	return sq >= a1 && sq <= h8 && board120[sq] != OB;
}

inline bool isValidPromotionPiece(int p) {
	return ( p >= wn && p <= wq ) || ( p >= bn && p <= bq );
}

extern void dumpAll();

#ifndef NDEBUG
extern void raiseAssertionFailure(char const * msg, char const * file, int line);
#define ASSERT(expr) if (!(expr)) raiseAssertionFailure(#expr, __FILE__, __LINE__)
#else
#define ASSERT(expr)
#endif /* NDEBUG */

#endif
