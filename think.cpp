#include "chessboard.hpp"

int chessboard::staticEval() {
	
	int pieceVals[] = {EM, 100, 320, 330, 500, 900, 20000, 100, 320, 330, 500, 900, 20000};
	int val = 0;
	
	if ( side == white ) {
		for(int piece = wp; piece <= wq; piece++) {
			val += ( pieceList[piece].size() * pieceVals[piece] );
		}
	}
	
	else {
		for(int piece = bp; piece <= bq; piece++) {
			val += ( pieceList[piece].size() * pieceVals[piece] );
		}
	}
	
	vector<Move> currMoveList;
	generateAllMoves(currMoveList);
	
	vector<Move> oppMoveList;
	side = !side;
	generateAllMoves(oppMoveList);
	side = !side;
	
	val += ( currMoveList.size() - oppMoveList.size() );
	
	return val;
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
		int score = negamax(4);
		undoMove(move);
		
		if ( score >= maxScore ) {
			bestMove = move;
		}
	}
	
	return bestMove;
}
