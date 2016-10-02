#include "chessboard.hpp"

ULL chessboard::hashList[13][64];
ULL chessboard::sideHash[2];
ULL chessboard::whiteCastleHash[2];
ULL chessboard::blackCastleHash[2];
ULL chessboard::enPassantHash[64];

void initHash() {
	
	// Intitialize the hash lists
	for(int square = 0; square < 64; square++) {
		chessboard::hashList[0][square] = 0;
	}
	
	for(int piece = wp; piece <= bk; piece++ ) {
		for(int square = 0; square < 64; square++) {
			chessboard::hashList[piece][square] = rand();
		}
	}
	
	for(int i = 0; i < 2; i++) {
		chessboard::whiteCastleHash[i] = rand();
		chessboard::blackCastleHash[i] = rand();
	}
	
	chessboard::sideHash[black] = rand();
	chessboard::sideHash[white] = rand();
	
	for(int square = 0; square < 64; square++) {
		chessboard::enPassantHash[square] = rand();
	} 
	
}
