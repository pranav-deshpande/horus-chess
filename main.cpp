#include "chessboard.hpp"
#include "move.hpp"
#include "data.hpp"

int main() {
	initHash();
	setUpDebugging();
	
	//cin.rdbuf()->setbuf(NULL, 0);
	cout.setf(ios::unitbuf);
	
	chessboard b;
	int engineSide = white;
	
	string command;
	
	cin >> command;
	if ( command == "xboard" ) {
		cout << endl;
		int temp;
		cin >> command >> temp;
		if ( command == "protover" && temp >= 2 ) {
			cout << "feature sigint=0 sigterm=0 done=1" << endl;
			while(true) {
				cin >> command;
				
				if ( command == "quit" ) break;
				
				else if ( command == "force" ) {
					
					while(true) {
						cin >> command;
						if (command == "new") {
						 	chessboard a;
						 	b = a;
						 	engineSide = black;
						  	break;
						}
						else if ( command == "go" ) {
							engineSide = b.side;
							Move move = b.findMove();
							b.playMove(move);
							move.printMove(b.side);
							cout << endl;
							break;
						}
						else {
							Move move = b.parseMoveFromString(command);
							b.playMove(move);
						}
					}
				}
				
				else if ( command == "new" ) {
					chessboard a;
					b = a;
				}
				
				else if ( command == "go" ) {
					engineSide = b.side;
					Move move = b.findMove();
					b.playMove(move);
					move.printMove(b.side);
					cout << endl;
				}	
				
				else {
					Move move = b.parseMoveFromString(command);
					b.playMove(move);
				}
			}
		}
	}
	
	return 0;	
}
