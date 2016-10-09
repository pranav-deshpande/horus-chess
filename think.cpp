#include "chessboard.hpp"

int chessboard::staticEval() {
	
	int pieceVals = {EM, 100, 320, 330, 500, 900, 20000, 100, 320, 330, 500, 900, 20000};
	int val = 0;
	
	if ( side == white )
		for(int piece = wp; piece <= wq; piece++) {
			val += ( pieceList[piece].size() * piece );
		}
	}
	
	else {
		for(int piece = bp; piece <= bq; piece++) {
			val += ( pieceList[piece].size() * piece );
		}
	}
	
	return val;
}

int chessboard::alphaBetaNegamax(int alpha, int beta, int depth) {
	
	if ( depth == 0 ) staticEval();
	
	vector <Move> childNodes;
	generateAllMoves(childNodes);
	
	int bestValue = -INT_MAX;
	
	for(vector<Move>::iterator it = childNodes.begin(); it != childNodes.end(); it++) {
		
		if ( bestValue >= beta ) break;
		if ( bestValue > alpha ) alpha = bestValue;
		
		playMove(*it);
		int val = -alphaBetaNegamax(alpha, beta, depth - 1);
		undoMove(*it);
		
		if ( val > bestValue ) bestValue = val;
	}
	
	return bestValue;
}
