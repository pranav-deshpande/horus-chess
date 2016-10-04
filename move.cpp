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

Move::Move(bool iscastle, int Castle) {
	isCastle = iscastle; // which will be true only if this has been called..
	castle = Castle;
	isEnPassant = false;
	from = to = EM;
	currPiece = capturedPiece = promotedPiece = EM;	
}
/*
Move::Move(string move) {
	
	if ( move[0] != 'O' ) {
	
		from = board64[ reverseSquareMapping[ move.substr(0,2) ] ];
		to = board64[ reverseSquareMapping[ move.substr(2, 4) ] ];
	
		// Temporarily set currPiece and capturePiece to zero
		// After being passed to chessboard::playMove, they get initialized properly
		// Since we are passing by reference, undoMove will not cause a problem later
		currPiece = EM;
		capturedPiece = EM;
			
		if ( move.length() == 5 )
			promotedPiece = reversePieceChars[ move[4] ];
		else
			promotedPiece = EM;
		
		if ( move.length() == 6 )
			enPassantSquare = reverseSquareMapping [ move.substr(5, 7) ];
		else 
			enPassantSquare = EM;
		
		isCastle = false;
		castle = -1;
	}
	
	else {
		
		from = to = enPassantSquare = EM;
		currPiece = capturedPiece = promotedPiece = EM;	
		
		if ( move == "O-O" ) {
			isCastle = true;
			castle = 0;
		}
	
		if ( move == "O-O-O" ) {
			isCastle = true;
			castle = 1;
		}
	}
}
*/

void Move::printMove() {

	if ( isCastle == true) {
	/*	
		if ( castle == 0 ) {
			if ( b.side == white ) cout << "e1g1";
			else cout << "e8g8";
 		}
		
		if  (castle == 1 ) { 
			if ( b.side == white ) cout << "e1c1";
			else cout << "e8c8";
		}
 		*/
 	}
	
	else {
		cout << squareMapping[ board120[from] ] << squareMapping[ board120[to] ];
		if(promotedPiece != EM) {
			cout << char(promotedPiece) ;
		}
	}
}
