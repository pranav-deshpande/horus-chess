#include "move.hpp"

// Member function definitions
// Blank move
Move::Move() {
	from = to = EM;
	currPiece = capturedPiece = EM;
	promotedPiece = EM;
	isEnPassant = false;
	isCastle = false;
	castle = -1;
}

// Normal/capture moves
Move::Move(int init_pos, int final_pos) {
	from = init_pos;
	to = final_pos;
	promotedPiece = EM;
	isEnPassant = false;
	isCastle = false;
	castle = -1;

	// Temporarily set to zero, will be set once it goes into playMove()
	currPiece = capturedPiece = EM;

}

// Enpassant moves
Move::Move(int init_pos) {
	from = init_pos;
	to = EM;
	promotedPiece = EM;
	isEnPassant = true; //Passing only the pawn=>enpass which will be true only, this is required to identify the type of move in playMove()
	isCastle = false;
	castle = -1;
	
	// Temporarily set to zero, will be set once it goes into playMove()
	currPiece = capturedPiece = EM;
}

// Pawn promotion moves
Move::Move(int init_pos, int final_pos, int Promote) {
	from = init_pos;
	to = final_pos;
	promotedPiece = Promote;
	isEnPassant = false;
	isCastle = false;
	castle = -1;
	
	// Temporarily set to zero, will be set once it goes into playMove()
	currPiece = capturedPiece = EM;
}

// Castling moves
Move::Move(bool iscastle, int Castle) {
	isCastle = iscastle; // which will be true only if this has been called..
	castle = Castle;
	isEnPassant = false;
	from = to = EM;
	currPiece = capturedPiece = promotedPiece = EM;	
}

void Move::printMove(int side) {

	if ( isCastle == true) {

		if ( castle == 0 ) {
			if ( side == white ) cout << "e1g1";
			else cout << "e8g8";
 		}
		
		if  (castle == 1 ) { 
			if ( side == white ) cout << "e1c1";
			else cout << "e8c8";
		}
 	}
	
	else {
		cout << squareMapping[ board120[from] ] << squareMapping[ board120[to] ];
		if(promotedPiece != EM) {
			cout << char(promotedPiece) ;
		}
	}
}
