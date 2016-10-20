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
Move::Move(int init_pos, int final_pos, int *board) {
	ASSERT(isValidSquare(init_pos));
	ASSERT(isValidSquare(final_pos));
	ASSERT(init_pos != final_pos);

	from = init_pos;
	to = final_pos;
	currPiece = board[from];
	capturedPiece = board[to];
	promotedPiece = EM;
	isEnPassant = false;
	isCastle = false;
	castle = -1;
}

// Enpassant moves
Move::Move(bool isenPassant, int init_pos, int final_pos, int *board) {
	ASSERT(isValidSquare(init_pos));

	from = init_pos;
	to = final_pos;
	currPiece = board[from];
	capturedPiece = ( currPiece == wp ) ? bp : wp;
	promotedPiece = EM;
	isEnPassant = isenPassant; // (True, since I am passing it)
	isCastle = false;
	castle = -1;
}

// Pawn promotion moves
Move::Move(int init_pos, int final_pos, int Promote, int *board) {
	ASSERT(isValidSquare(init_pos));
	ASSERT(isValidSquare(final_pos));
	ASSERT(init_pos != final_pos);
	ASSERT(isValidPromotionPiece(Promote));

	from = init_pos;
	to = final_pos;
	currPiece = board[from];
	capturedPiece = board[to];
	promotedPiece = Promote;
	isEnPassant = false;
	isCastle = false;
	castle = -1;
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
			cout << "O-O";
 		}
		
		if  (castle == 1 ) { 
			cout << "O-O-O";
		}
 	}
	
	else {
		cout << squareMapping[ board120[from] ] << squareMapping[ board120[to] ];
		if(promotedPiece != EM) {
			char x = tolower( pieceChars[promotedPiece] ) ;
			cout << x;
		}
	}
}

string Move::MoveToString(int side) {
	
	string m = "";
	
	if ( isCastle == true) {
		
		if ( castle == 0 ) {
			m = "O-O";		
 		}
		
		if  (castle == 1 ) { 
			m = "O-O-O";
		}
 	}
	
	else {
		m = squareMapping[ board120[from] ] + squareMapping[ board120[to] ];
		
		if(promotedPiece != EM) {
			m = m + string(1, tolower( pieceChars[promotedPiece] ) );
		}
	}
	return m;
}

bool Move::isNull() {
	return (from == EM && to == EM) && !isCastle;
}
