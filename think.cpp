#include "chessboard.hpp"

// Piece square tables for the evaluation function
int pTable[] = {
	 0,  0,  0,  0,  0,  0,  0,  0,
	50, 50, 50, 50, 50, 50, 50, 50,
	10, 10, 20, 30, 30, 20, 10, 10,
	 5,  5, 10, 25, 25, 10,  5,  5,
	 0,  0,  0, 20, 20,  0,  0,  0,
	 5, -5,-10,  0,  0,-10, -5,  5,
	 5, 10, 10,-20,-20, 10, 10,  5,
	 0,  0,  0,  0,  0,  0,  0,  0
};

int nTable[] = {
	-50,-40,-30,-30,-30,-30,-40,-50,
	-40,-20,  0,  0,  0,  0,-20,-40,
	-30,  0, 10, 15, 15, 10,  0,-30,
	-30,  5, 15, 20, 20, 15,  5,-30,
	-30,  0, 15, 20, 20, 15,  0,-30,
	-30,  5, 10, 15, 15, 10,  5,-30,
	-40,-20,  0,  5,  5,  0,-20,-40,
	-50,-40,-30,-30,-30,-30,-40,-50,
};

int bTable[] = {
	-20,-10,-10,-10,-10,-10,-10,-20,
	-10,  0,  0,  0,  0,  0,  0,-10,
	-10,  0,  5, 10, 10,  5,  0,-10,
	-10,  5,  5, 10, 10,  5,  5,-10,
	-10,  0, 10, 10, 10, 10,  0,-10,
	-10, 10, 10, 10, 10, 10, 10,-10,
	-10,  5,  0,  0,  0,  0,  5,-10,
	-20,-10,-10,-10,-10,-10,-10,-20,
};

int rTable[] = {
	 0,  0,  0,  0,  0,  0,  0,  0,
	  5, 10, 10, 10, 10, 10, 10,  5,
	 -5,  0,  0,  0,  0,  0,  0, -5,
	 -5,  0,  0,  0,  0,  0,  0, -5,
	 -5,  0,  0,  0,  0,  0,  0, -5,
	 -5,  0,  0,  0,  0,  0,  0, -5,
	 -5,  0,  0,  0,  0,  0,  0, -5,
	  0,  0,  0,  5,  5,  0,  0,  0
};

int qTable[] = {
	-20,-10,-10, -5, -5,-10,-10,-20,
	-10,  0,  0,  0,  0,  0,  0,-10,
	-10,  0,  5,  5,  5,  5,  0,-10,
	 -5,  0,  5,  5,  5,  5,  0, -5,
	  0,  0,  5,  5,  5,  5,  0, -5,
	-10,  5,  5,  5,  5,  5,  0,-10,
	-10,  0,  5,  0,  0,  0,  0,-10,
	-20,-10,-10, -5, -5,-10,-10,-20
};

int mirror[] = {
	56, 57, 58, 59, 60, 61, 62, 63,
	48, 49, 50, 51, 52, 53, 54, 55,
	40, 41, 42, 43, 44, 45, 46, 47,
	32, 33, 34, 35, 36, 37, 38, 39,
	24, 25, 26, 27, 28, 29, 30, 31,
	16, 17, 18, 19, 20, 21, 22, 23,
	 8,  9, 10, 11, 12, 13, 14, 15,
	 0,  1,  2,  3,  4,  5,  6,  7
};

int chessboard::staticEval() {
	
	int pieceVals[] = {EM, 100, 320, 330, 500, 900, 20000, 100, 320, 330, 500, 900, 20000};
	int val = 0, blackVal = 0, whiteVal = 0;
	int square;
	
		for(int piece = wp; piece <= wq; piece++) {
			for(unordered_set<int>::iterator it = pieceList[piece].begin(); it != pieceList[piece].end(); it++) {
				whiteVal += pieceVals[piece];
				square = mirror[ board120[*it] ];
				if (piece == wp) whiteVal += pTable[square];
				else if (piece == wn) whiteVal += nTable[square];
				else if (piece == wb) whiteVal += bTable[square];
				else if (piece == wr) whiteVal += rTable[square];
				else if (piece == wq) whiteVal += qTable[square];
			}
		}
		
		for(int piece = bp; piece <= bq; piece++) {
			for(unordered_set<int>::iterator it = pieceList[piece].begin(); it != pieceList[piece].end(); it++) {
				blackVal += pieceVals[piece];
				square = board120[*it];
				if (piece == bp) blackVal += pTable[square];
				else if (piece == bn) blackVal += nTable[square];
				else if (piece == bb) blackVal += bTable[square];
				else if (piece == br) blackVal += rTable[square];
				else if (piece == bq) blackVal += qTable[square];
			}
		}
	
	val = whiteVal - blackVal;
	
	if ( side == white ) return val;
	else return -val;
	
	
}

int chessboard::negamax(int depth) {
	
	if ( depth == 0 ) return staticEval();
	
	vector <Move> childNodes;
	generateAllMoves(childNodes);
	
	int bestValue = -INT_MAX;
	
	for(vector<Move>::iterator it = childNodes.begin(); it != childNodes.end(); it++) {
		
		playMove(*it);
		int val = -negamax(depth - 1);
		undoMove(*it);
		
		if ( val > bestValue ) bestValue = val;
	}
	
	return bestValue;
}

Move chessboard::findMove() {
	
	vector<Move> moveList;
	generateAllMoves(moveList);
	
	Move bestMove;
	int maxScore = -INT_MAX;

	for(vector<Move>::iterator it = moveList.begin(); it!= moveList.end(); it++) {
		
		Move move = *it;
		
		playMove(move);
		int score = -negamax(3);
		undoMove(move);
		
		if ( score > maxScore ) {
			bestMove = move;
			maxScore = score;
		}
	}
	
	return bestMove;
}
