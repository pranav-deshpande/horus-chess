#include "move.hpp"

// Member function definitions
Move::Move() {
	from = to = EM;
	currPiece = capturedPiece = EM;
	promotedPiece = EM;
	isEnPassant = false;
	isCastle = false;
	castle = 0;
}

// Normal/capture moves
Move::Move(int init_pos, int final_pos, int currpiece, int capturedpiece) {
	ASSERT(isValidSquare(init_pos));
	ASSERT(isValidSquare(final_pos));
	ASSERT(init_pos != final_pos);

	from = init_pos;
	to = final_pos;
	currPiece = currpiece;
	capturedPiece = capturedpiece;
	promotedPiece = EM;
	isEnPassant = false;
	isCastle = false;
	castle = 0;
}

// Enpassant moves
Move::Move(bool isenPassant, int init_pos, int final_pos, int currpiece, int capturedpiece) {
	ASSERT(isValidSquare(init_pos));

	from = init_pos;
	to = final_pos;
	currPiece = currpiece;
	capturedPiece = capturedpiece;
	promotedPiece = EM;
	isEnPassant = isenPassant; // (True, since I am passing it)
	isCastle = false;
	castle = 0;
}

// Pawn promotion moves
Move::Move(int init_pos, int final_pos, int currpiece, int capturedpiece, int Promote) {
	ASSERT(isValidSquare(init_pos));
	ASSERT(isValidSquare(final_pos));
	ASSERT(init_pos != final_pos);
	ASSERT(isValidPromotionPiece(Promote));

	from = init_pos;
	to = final_pos;
	currPiece = currpiece;
	capturedPiece = capturedpiece;
	promotedPiece = Promote;
	isEnPassant = false;
	isCastle = false;
	castle = 0;
}

// Castling moves
Move::Move(bool iscastle, int Castle) {
	isCastle = iscastle; // which will be true only if this has been called..
	castle = Castle;
	isEnPassant = false;
	from = to = EM;
	currPiece = capturedPiece = promotedPiece = EM;	
}

string Move::MoveToString() {
	
	string m = "";
	
	if ( isCastle == true) {
		if ( castle == wOO ) m = "e1g1";
		else if ( castle == wOOO ) m = "e1c1";
		else if ( castle == bOO ) m = "e8g8";
		else if ( castle == bOOO ) m = "e8c8";
 	}
	
	else {
		m = m + squareMapping[ board120[from] ] + squareMapping[ board120[to] ];
		
		if(promotedPiece != EM) {
			m = m + string(1, tolower( pieceChars[promotedPiece] ) );
		}
	}
	return m;
}

bool Move::isNull() {
	return ( from == EM && to == EM ) && !isCastle;
}
