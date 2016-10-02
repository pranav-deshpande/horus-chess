#include "chessboard.hpp"
#include "move.hpp"

/*
int main() {
	initHash();
	string test1 = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	string test2 = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq -";
	string test3 = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -";
	string test4a = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
	string test4b = "r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1";
	string test5 = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8";
	string test6 = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";
	
	chessboard b;
	
	b = chessboard(test1);
	cout << "Position 1: " << test1 << endl << endl;
	for(int i = 1; i <= 6; i++) {
		cout << i << " " << b.perft(i) << endl;
	}
	cout << endl << endl;
	
	b = chessboard(test2);
	cout << "Position 2: " << test2 << endl << endl;
	for(int i = 1; i <= 5; i++) {
		cout << i << " " << b.perft(i) << endl;
	}
	cout << endl << endl;
	
	b = chessboard(test3);
	cout << "Position 3: " << test3 << endl;
	for(int i = 1; i <= 7; i++) {
		cout << i << " " << b.perft(i) << endl;
	}
	cout << endl;
	
	b = chessboard(test4a);
	cout << "Position 4a: " << test4a << endl << endl;
	for(int i = 1; i <= 6; i++) {
		cout << i << " " << b.perft(i) << endl;
	}
	cout << endl << endl;
	
	b = chessboard(test4b);
	cout << "Position 4b: " << test4b << endl << endl;
	for(int i = 1; i <= 6; i++) {
		cout << i << " " << b.perft(i) << endl;
	}
	cout << endl << endl;
	
	b = chessboard(test5);
	cout << "Position 5: " << test5 << endl << endl;
	for(int i = 1; i <= 5; i++) {
		cout << i << " " << b.perft(i) << endl;
	}
	cout << endl << endl;
	
	b = chessboard(test6);
	cout << "Position 6: " << test6 << endl << endl;
	for(int i = 1; i <= 5; i++) {
		cout << i << " " << b.perft(i) << endl;
	}
	cout << endl << endl;

	return 0;
}
*/

int main() {
	initHash();
	string test = "n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1";
	chessboard b(test);
	for(int i = 1; i <= 6; i++) cout << i << " " << b.perft(i) << endl;
	return 0;
}

