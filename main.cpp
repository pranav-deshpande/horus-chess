#include "chessboard.hpp"
#include "move.hpp"
#include "data.hpp"

int main() {
	initHash();
	setUpDebugging();
	
	chessboard b;
	
	string input;
	
	getline(cin, input);
	if ( input == "xboard" ) cout << '\n';
	else {
		cout << "Error! Exiting!" << endl;
		exit(1);
	} 

	getline(cin, input);
	
	if ( input == "protover 2" ) 
		cout << "done=1\n";
	else {
		cout << "Error! Exiting!" << endl;
		exit(1);
	}  

	while(true) {
		
		cin >> input;
		
		if ( input == "quit" ) {
			cout << '\n';
			break;
		}
		
		else if ( input == "force" ) {
			cout << '\n';
			while(true) {
				cin >> input;
				Move m = b.parseMoveFromString(input);
				b.playMove(m);
				cout << '\n';
			}
		}

		else if ( input == "new" ) {
			chessboard a;
			b = a;
		}
		
		else if ( input == "go" ) {
			Move m = b.findMove();
			b.playMove(m);
			cout << "usermove ";
			m.printMove(b.side);
			cout << '\n';
		}
		
		else break;
	}
	return 0;
}

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
/*
int main() {
	initHash();
	setUpDebugging();
	
	chessboard b;
	
	/*string input;
	cin >> input;
	if ( input == "xboard" )
		cout << '\n';
	else exit(1);
	
	/
	
	
	while(true) {
		getchar();
		Move move = b.findMove();
		b.playMove(move);
		b.printMinimalBoard();
	}
	return 0;
}*/
