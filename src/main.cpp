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

#include "chessboard.hpp"
#include "move.hpp"
#include "data.hpp"

static chessboard *theBoard = NULL;

void dumpAll() {
	if (theBoard != NULL) {
		theBoard->printGame();
		theBoard->printBoard();
	}
}

EndOfGameReason handleEndOfGame(chessboard &b) {
	EndOfGameReason reason = NoEndOfGame;
    if ( b.isEndOfGame(reason) ) {
    	if ( reason == Mate ) {
    		if ( ( !b.side ) == white ) {
    			cout << "1-0 {White mates}" << endl;
    		}
    		else {
    			cout << "0-1 {Black mates}" << endl;
    		}
    	}

    	else {
    		cout << "1/2-1/2 ";
    		if ( reason == Stalemate ) {
    			cout << "{Stalemate}" << endl;
    		}
    		else if ( reason == FiftyMoveRule ) {
    			cout << "{Draw by fifty move rule}" << endl;
    		}
    		else if ( reason == ThreeFoldRepetition ) {
    			cout << "{Draw by repetition}" << endl;
    		}
    		else if ( reason == InsufficientMaterial ) {
    			cout << "{Draw by insufficient material}" << endl;
    		}
    	}
    }
    return reason;
}

int main() {
    initHash();
    setUpDebugging();
    int engineSide = empty;
    cout << "feature done=0" << endl;
    cout.setf(ios::unitbuf);

    chessboard b;
    theBoard = &b;

    bool isConsoleMode = true;

    string command;

    while (true) {
        if (isConsoleMode) {
            cout << "# Your command: ";
            flush(cout);
        }
        cin >> command;
        cout << "# received command: " << command << endl;

        if ( command == "" ) continue; // in console mode, an empty command should not terminate the engine

        if ( command == "quit" ) break;

        if ( command == "xboard" ) {
            cout << endl;
            isConsoleMode = false;
        }

        else if ( command == "protover" ) {
            int temp;
            cin >> temp;
            if ( temp >= 2 ) {
                cout << "feature ping=1 time=0 sigint=0 sigterm=0 usermove=1 setboard=1 done=1" << endl;
            }
        }

        else if ( command == "ping" ) {
            int param;
            cin >> param;
            cout << "# received parameter: " << param << endl;
            cout << "pong " << param << endl;
        }

        else if ( command == "force" ) {
            engineSide = empty;
        }

        else if ( command == "new" ) {
            b.resetToInitialPosition();
            engineSide = black;
        }

        else if ( command == "setboard" ) {
        	string fen;
        	cin.get();
        	getline(cin, fen);
        	cout << "# received parameter: " << fen << endl;
      		// Now I should add some kind of method to check whether the user gave me a valid position!!
      		b.resetToFEN(fen);
      	}

        else if ( command == "go" ) {
            engineSide = b.side;
        }

        else if ( command == "usermove" ) {
            string param;
            cin >> param;
            cout << "# received parameter: " << param << endl;
            Move move = b.parseMoveFromString(param);
            if (move.isNull()) {
                cout << "Error (illegal move): " << param << endl;
            } else {
                b.playMove(move);
                b.printMinimalBoard();
            }

            if( handleEndOfGame(b) != NoEndOfGame) engineSide = empty;
        }

        else if ( command == "undo" ) {
            Move move = b.getLastMove();
            b.undoMove(move);
            cout << "# Move undone: " << move.MoveToString() << endl;
        }

        else if ( command == "remove" ) {
            Move move = b.getLastMove();
            b.undoMove(move);
            cout << "# Move undone: " << move.MoveToString() << endl;
            move = b.getLastMove();
            b.undoMove(move);
            cout << "# Move undone: " << move.MoveToString() << endl;
        }

        else if ( command == "accepted" ) {
            string temp;
            cin >> temp;
            continue;
        }

        else if ( command == "selftest" ) {
            samplePerftTest();
        }

        else {
            cout << "# ignoring unknown command: " << command << endl;
            continue;
        }

        if (engineSide == b.side) {
            cout << "# calculating engine move ..." << endl;
            Move move = b.findMove();
            cout << "move ";
			cout << move.MoveToString() << endl;
            cout << endl;
            b.playMove(move);
            b.printMinimalBoard();

           if( handleEndOfGame(b) != NoEndOfGame) engineSide = empty;
        }
    }

    return 0;
}
