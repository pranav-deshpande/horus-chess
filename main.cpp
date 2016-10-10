#include "chessboard.hpp"
#include "move.hpp"
#include "data.hpp"
#define empty -1
int main() {
    initHash();
    setUpDebugging();

    cout << "feature done=0" << endl;
    cout.setf(ios::unitbuf);

    chessboard b;
    int engineSide = empty;

    string command;

    while (true) {
        cin >> command;

        if ( command == "" ) continue; // in console mode, an empty command should not terminate the engine

        if ( command == "quit" ) break;

        if ( command == "xboard" ) {
            cout << endl;
        }

        else if ( command == "protover" ) {
            int temp;
            cin >> temp;
            if ( temp >= 2 ) {
                cout << "feature sigint=0 sigterm=0 usermove=1 done=1" << endl;
            }
        }

        else if ( command == "force" ) {
            engineSide = empty; // to be added in data.hpp
        }

        else if ( command == "new" ) {
            chessboard a;
            b = a;
            engineSide = black;
        }

        else if ( command == "go" ) {
            engineSide = b.side;
        }

        else if ( command == "usermove" ) {
            cin >> command;
            Move move = b.parseMoveFromString(command);
            b.playMove(move);
        }
        
       	else continue; // unknown command

        if (engineSide == b.side) {
            Move move = b.findMove();
            b.playMove(move);
            cout << "move ";
            move.printMove(b.side);
            cout << endl;
        }
    }

    return 0;
}
