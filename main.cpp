#include "chessboard.hpp"
#include "move.hpp"
#include "data.hpp"
/*
int main() {
	initHash();
	setUpDebugging();
	string test = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; 
	runPerftTests();
	
	// Just as a sample
	debugPerft(test, 3);
}
*/

int main() {
	initHash();
	setUpDebugging();
	
	chessboard b;
	
	b.printMinimalBoard();
	
	while(true) {
		getchar();
		Move move = b.findMove();
		b.playMove(move);
		b.printMinimalBoard();
	}
	return 0;
}
