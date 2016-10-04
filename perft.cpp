#include "chessboard.hpp"

ULL chessboard::perft(int depth) {
	
	generateAllMoves();
	vector <Move> test = moveList;
	
	ULL nodes = 0;
	
	if ( depth == 0 ) return 1; // if someone calls debugMoveGen with argument 1
	
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
	printMinimalBoard();
	
	for(vector<Move>::iterator it = moveList.begin(); it != moveList.end(); it++) {
		playMove(*it);
		printMinimalBoard();
		getchar();
		undoMove(*it);
		printMinimalBoard();
		getchar();
	}
}

// Note that this function is not a member of the chessboard class
void runPerftTests() {
	ifstream fin("perftTests");
	ofstream fout("perftResults");
	
	string test;
	int position = 1;
	int perftDepth = 5; // Some can be calculated to 6 or 7 as well
	
	fout << "Positions are as given on https://chessprogramming.wikispaces.com/Perft+Results" << endl;
	fout << "The 8th posiion is taken from http://www.rocechess.ch/perft.html" << endl;
	fout << endl;
	
	while ( getline(fin, test) ) {
		fout << "Position " << position << ": " << test << "\n\n";
		chessboard b(test);
		for( int i = 1; i <= perftDepth; i++) {
			fout << i << ' ' << b.perft(i) << endl;
		}
		fout << "\n";
		position++;
	}
	
	fin.close();
	fout.close();
	
}

void debugPerft(string &test, int depth) {

	if ( depth < 0 ) {
		cout << "Error - Depth should be greater than zero" << endl;
		exit(1);
	}
	
	chessboard b(test);
	
	b.generateAllMoves();
	vector <Move> moves = b.moveList;
	ULL ans1 = 0, p;
	
	cout << "Position: " << test << endl;
	cout << "Depth: " << depth << "\n\n";
	
	for(vector <Move>::iterator it = moves.begin(); it != moves.end(); it++) {
		it -> printMove();
		cout << ": ";
		b.playMove(*it);
		p = b.perft(depth-1);
		cout << p << endl;
		ans1 += p;
		b.undoMove(*it);
	}
	
	ULL ans2 = b.perft(depth);

	assert(ans1 == ans2);
	
	cout << endl << "Total: " << ans1 << endl;

}
