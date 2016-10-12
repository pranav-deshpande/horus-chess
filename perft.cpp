#include "chessboard.hpp"

ULL chessboard::perft(int depth) {
	
	vector <Move> moveList;
	generateAllMoves(moveList);
	
	ULL nodes = 0;
	
	if ( depth == 0 ) return 1; // if someone calls debugMoveGen with argument 1
	
	if ( depth == 1 ) {
		return moveList.size();
	}
	
	for(vector<Move>::iterator it = moveList.begin(); it != moveList.end(); it++) {
		playMove(*it);
		nodes += perft(depth-1);
		undoMove(*it);
	}
	
	return nodes;
}

// This function is used to go through the moves one by one during perft testing once we have determined
// that a line of moves is wrong.
void chessboard::test() {
	
	vector <Move> moveList;
	generateAllMoves(moveList);
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
	
	vector <Move> moveList;
	b.generateAllMoves(moveList);

	ULL ans1 = 0, p;
	
	cout << "Position: " << test << endl;
	cout << "Depth: " << depth << "\n\n";
	
	for(vector <Move>::iterator it = moveList.begin(); it != moveList.end(); it++) {
		cout << it -> MoveToString(b.side);
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

void samplePerftTest() {
	cout << "Running sample perft tests! This will take a long time." << endl;
	cout << "The fen strings are in the perftTests file. The results will be output to the file perftResults." << endl;
	
	runPerftTests();
	
	// Just as a sample
	string test = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; 
	debugPerft(test, 3);
}
