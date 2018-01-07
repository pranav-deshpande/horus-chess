/*
Horus - A Chess Engine created for learning Game AI techniques
Copyright (C) 2016 Pranav Deshpande

This file is a part of Horus.

Horus is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

Horus is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Horus. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __CHESSBOARD__
#define __CHESSBOARD__

#include "data.hpp"
#include "move.hpp"

class chessboard {
private:

	// Basic Board Representation and Data
	int8_t board[BOARDSIZE];
	int plies, moves;

	int actualPlies;

	int fiftyMoveRule;
	bool whiteCastlePerms[2];
	bool blackCastlePerms[2];
	int enPassantSquare[2]; // enPassantSquare[white] => white can capture it

	// Makes generating the moves efficient, we only have to iterate over the piece list rather 64 squares
	// PieceList - an array of integer sets
	// Also makes checking the legality of the moves easier
	unordered_set <int> pieceList[13];

	// Maintain the position hashes for the three fold repetition rule
	ULL uniqueKey;

	// Maintain flag indicating whether king of moving side is in check
	bool inCheck;

	// Maintain set of pieces currently pinned to king of moving side
	ULL pins;

	// To store moves while we are searching the game tree

	vector < array<bool, 4> > castleList;
	vector < pair<int, int> > enPassSqList;
	vector <ULL> keyList;
	vector <int> fiftyMoveRuleHistory;

	// Member Functions:
	void initEmptyBoard();

	void fenSetup(string &fen);

	void initPieceList();
	void initUniqueKey();

	void insertPiece(int piece, int square);
	void erasePiece (int piece, int square);

	bool isSquareSafe(int square, int Side);
	bool isSquareAttacked(int square, int Side);
	bool isMoveValid(Move &move);
	void addMove(Move &move, vector <Move> &moveList);
	int staticEval();
	int negamax(int depth);
	int alphaBeta(int alpha, int beta, int depth, int distToRoot);
	void orderMoves(vector <Move> &moveList);
	static bool moveCompare(Move &lhs, Move &rhs);

	int Quiescence(int alpha, int beta, int distToRoot);

	bool isFiftyMovesDraw();
	bool isRepetition();
	bool isThreeFoldRepetition();
	bool isDrawByInsufficientMaterial();
	bool checkDraw();

#ifndef NDEBUG
	bool suppressValidityCheck;
#endif /* NDEBUG */



public:
	chessboard();
	chessboard(string &fen);
	void resetToFEN(string &fen);
	void resetToInitialPosition();
	void playMove(Move &move);
	void undoMove(Move &move);
	void printBoard();
	void printMinimalBoard();
	void printGame();
	void generateAllMoves(vector <Move> &moveList);
	ULL perft(int depth);
	Move getLastMove();

	bool isValid();

	static ULL hashList[13][64];
	static ULL whiteCastleHash[2];
	static ULL blackCastleHash[2];
	static ULL sideHash[2];
	static ULL enPassantHash[64];

	void test();

	// To store the moves played during the game, i.e. to store the game
	vector <Move> game;

	int side;

	void updateInCheck();

	Move findMove();
	bool isEndOfGame(EndOfGameReason &reason);
	Move parseMoveFromString(string m);
	ULL getPins();
	int kingSquare(int side);
};

#endif
