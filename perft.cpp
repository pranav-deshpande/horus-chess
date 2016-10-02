#include "chessboard.hpp"
ULL chessboard::perft(int depth) {
	
	generateAllMoves();
	vector <Move> test = moveList;
	
	ULL nodes = 0;
	
	if ( depth == 1 ) {
		return test.size();
	}
	
	for(vector<Move>::iterator it = test.begin(); it != test.end(); it++) {
		playMove(*it);
		nodes += perft(depth-1);
		undoMove(*it);
	}
	
	return nodes;
}

// This function is used to go through the moves one by one during perft testing once we have determined
// that a line of moves is wrong.
void chessboard::test() {
	generateAllMoves();
	printBoard();
	for(vector<Move>::iterator it = moveList.begin(); it != moveList.end(); it++) {
		playMove(*it);
		printBoard();
		getchar();
		undoMove(*it);
		printBoard();
		getchar();
	}
}

