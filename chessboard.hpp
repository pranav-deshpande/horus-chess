#ifndef __CHESSBOARD__
#define __CHESSBOARD__

#include "data.hpp"
#include "move.hpp"

class chessboard {
	friend class Move;
private:
	
	// Basic Board Representation and Data
	int board[BOARDSIZE];
	int side, plies, moves;

	int actualPlies;

	int fiftyMoveRule, threeFold;
	bool whiteCastlePerms[2];
	bool blackCastlePerms[2];
	int enPassantSquare[2]; // enPassantSquare[white] => white can capture it
	
	// Makes generating the moves efficient, we only have to iterate over the piece list rather 64 squares
	// PieceList - an array of integer sets
	// Also makes checking the legality of the moves easier
	unordered_set <int> pieceList[13];
	
	// Maintain the position hashes for the three fold repetition rule
	ULL uniqueKey;
	
	// To store moves while we are searching the game tree 

	vector < array<bool, 4> > castleList;
	vector < pair<int, int> > enPassSqList;
	vector <ULL> keyList;
	
	// To store the moves actually played and the position hash during that time(for the fifty move rule)
	vector < pair<Move, ULL> > moveHistory;
	
	// Member Functions:
	void initEmptyBoard();

	void initPieceList();
	void initUniqueKey();

public:
	chessboard();
	chessboard(string &fen);
	void playMove(Move &move);
	void undoMove(Move &move);
	void printBoard();
	void generateAllMoves();
	bool isSquareSafe(int square, int Side);
	bool isSquareAttacked(int square, int Side);
	void addMove(Move &move);
	void fenSetup(string &fen);
	bool isMoveValid(Move &move);
	ULL perft(int depth);
	bool isValid();
	void printMinimalBoard();
	
	
	static ULL hashList[13][64];
	static ULL whiteCastleHash[2];
	static ULL blackCastleHash[2];
	static ULL sideHash[2];
	static ULL enPassantHash[64];
	void test();
	
		vector <Move> moveList;

};

#endif
