#include "move.hpp"

// Member function definitions
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
/*
Move::Move(string move) {
	
	if (Move == "e1g1" || move == "e1c1" || move == "e8g8" || move == "e8c8") {
		bool iscastle == true;
		
		if ( move == "e1g1" || move == "e8g8" ) {
			Move(iscastle, 0);
		}
		
		else {
			Move(iscastle, 1);
		}
	}
	
	else {
		// There is a problem - How do I know if the move is an enPassant Move?
		
		int From = board64[ reverseSquareMapping[ move.substr(0,2) ] ];
		int To = board64[ reverseSquareMapping[ move.substr(2, 4) ] ];
	
		if ( move.length() == 5 ) {
			int PromotedPiece = reversePieceChars[ move[4] ];
			Move(From, To, PromotedPiece);
		}
	
		else {
			Move(From, To);
		}
	}

}
*/

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
