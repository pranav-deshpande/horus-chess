#include "chessboard.hpp"

void chessboard::generateAllMoves(vector <Move> &moveList) {
	// It is expected that I send a blank vector, but still
	moveList.clear();
	
	// Inspired by the offset method for move generation given on https://chessprogramming.wikispaces.com/10x12+Board
	// However, my code isn't as compact as that one
	int pieceSide[] = { EM, white, white, white, white, white, white, black, black, black, black, black, black };
	int pieceDirections[] = {EM, EM, 8, 4, 4, 8, 8, EM, 8, 4, 4, 8, 8};
	
	int moveArr[13][8] = {
		{0, 0, 0, 0, 0, 0, 0, 0}, 
		{0, 0, 0, 0, 0, 0, 0, 0}, 
		{NM1, NM2, NM3, NM4, NM5, NM6, NM7, NM8}, 
		{TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, 0, 0, 0, 0}, 
		{UP, DOWN, RIGHT, LEFT, 0, 0, 0, 0}, 
		{TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, UP, DOWN, RIGHT, LEFT}, 
		{TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, UP, DOWN, RIGHT, LEFT}, 
		{0, 0, 0, 0, 0, 0, 0, 0}, 
		{NM1, NM2, NM3, NM4, NM5, NM6, NM7, NM8}, 
		{TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, 0, 0, 0, 0}, 
		{UP, DOWN, RIGHT, LEFT, 0, 0, 0, 0}, 
		{TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, UP, DOWN, RIGHT, LEFT}, 
		{TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, UP, DOWN, RIGHT, LEFT}, 
	};
		
	unordered_set<int> piecesList[13];
	
	for(int piece = wp; piece <= bk; piece++) {
		for(unordered_set<int>::iterator it = pieceList[piece].begin(); it != pieceList[piece].end(); it++) {
			piecesList[piece].insert(*it);
		}
	}
	
	Move move;

	if(side == white) {
		for(int piece = wp; piece <= wk; piece++) {
			for(unordered_set<int>::iterator it = piecesList[piece].begin(); it != piecesList[piece].end(); it++ ) {
				int currSquare = *it;
				int finalSquare;

				switch( piece ) {
		
				case wp:
					finalSquare = currSquare + UP;
		
					if ( board[finalSquare] == EM ) {
		
						if ( squareMapping[ board120[finalSquare] ].at(1) == '8' ) {
							move = Move(currSquare, finalSquare, wb);
							addMove(move, moveList);
				
							move = Move(currSquare, finalSquare, wn);
							addMove(move, moveList);
				
							move = Move(currSquare, finalSquare, wr);
							addMove(move, moveList);
				
							move = Move(currSquare, finalSquare, wq);
							addMove(move, moveList);
						}
			
						else {
							move = Move(currSquare, finalSquare);
							addMove(move, moveList);		
						}
					}
	
					finalSquare = currSquare + 2*UP;
		
					if ( board[finalSquare] != OB && board[finalSquare] == EM && squareMapping[ board120[currSquare] ].at(1) == '2' && board[finalSquare-UP] == EM) {
						move = Move(currSquare, finalSquare);
						addMove(move, moveList);
					}
		
					finalSquare = currSquare + TOP_LEFT;
		
					if ( board[finalSquare] != OB && board[finalSquare] != EM && pieceSide[ board[finalSquare] ] == black ) {
			
						if ( squareMapping[ board120[finalSquare] ].at(1) == '8' ) {
							move = Move(currSquare, finalSquare, wb);
							addMove(move, moveList);
				
							move = Move(currSquare, finalSquare, wn);
							addMove(move, moveList);
				
							move = Move(currSquare, finalSquare, wr);
							addMove(move, moveList);
				
							move = Move(currSquare, finalSquare, wq);
							addMove(move, moveList);
						}
			
						else {
							move = Move(currSquare, finalSquare);
							addMove(move, moveList);		
						}
					}
		
					if ( enPassantSquare[white] != EM && finalSquare == enPassantSquare[white] && board[ enPassantSquare[white] ] == EM ) {
						// in enPassant, we will set the square TO to empty due to the way we have coded playMove
						move = Move(currSquare);
						addMove(move, moveList);
					}
					 
					finalSquare = currSquare + TOP_RIGHT;
		
					if ( board[finalSquare] != OB && board[finalSquare] != EM && pieceSide[ board[finalSquare] ] == black ) {
			
						if ( squareMapping[ board120[finalSquare] ].at(1) == '8' ) {
							move = Move(currSquare, finalSquare, wb);
							addMove(move, moveList);
				
							move = Move(currSquare, finalSquare, wn);
							addMove(move, moveList);
				
							move = Move(currSquare, finalSquare, wr);
							addMove(move, moveList);
				
							move = Move(currSquare, finalSquare, wq);
							addMove(move, moveList);
						}
			
						else {
							move = Move(currSquare, finalSquare);
							addMove(move, moveList);		
						}
					}
		
					if ( enPassantSquare[white] != EM && finalSquare == enPassantSquare[white] && board[ enPassantSquare[white] ] == EM) {
						// in enPassant, we will set the square TO to empty due to the way we have coded playMove
						move = Move(currSquare);
						addMove(move, moveList);
					}
					break;
		
				case wn:
				case wk:
					for(int i = 0; i < pieceDirections[piece]; i++) {
						finalSquare = currSquare + moveArr[piece][i];
		
						if ( board[finalSquare] != OB && ( board[finalSquare] == EM || pieceSide[ board[finalSquare] ] == black ) ) {
							move = Move(currSquare, finalSquare);
							addMove(move, moveList);
						}
			
					}
					break;
	
				case wb:
				case wr:
				case wq:
					for(int i = 0; i < pieceDirections[piece]; i++) {
						int increment = moveArr[piece][i];
						finalSquare = currSquare + increment;
			
						while ( board[finalSquare] != OB ) {
				
							if ( board[finalSquare] == EM ) {
								move = Move(currSquare, finalSquare);
								addMove(move, moveList);
								finalSquare += increment;
							}
				
							else if ( pieceSide[ board[finalSquare] ] == black ) {
								move = Move(currSquare, finalSquare);
								addMove(move, moveList);
								break;
							}
				
							else {
								break;
							}
						}
					}
					break;
		
				default: break;
				}		
			}
		}
		// Now generate castle moves
		int castle = -1;
		bool isCastle = false;

		if ( whiteCastlePerms[0] == true && board[f1] == EM && board[g1] == EM && board[e1] == wk && board[h1] == wr ) {
			if ( isSquareSafe(e1, side) && isSquareSafe(g1, side) && isSquareSafe(f1, side) ) {
				isCastle = true;
				castle = 0;
				move = Move(isCastle, castle);
				addMove(move, moveList);
			}
		}
	
		if ( whiteCastlePerms[1] == true && board[b1] == EM && board[c1] == EM && board[d1] == EM && board[e1] == wk && board[a1] == wr ){
			if ( isSquareSafe(e1, side) && isSquareSafe(c1, side) && isSquareSafe(d1, side) ) {
				isCastle = true;
				castle = 1;
				move = Move(isCastle, castle);
				addMove(move, moveList);
			}
		}
	}	

	else {
		for(int piece = bp; piece <= bk; piece++) {
		 	for(unordered_set<int>::iterator it = piecesList[piece].begin(); it != piecesList[piece].end(); it++) {
				int currSquare = *it;
				int finalSquare;		

				switch( piece ) {
	
				case bp:
					finalSquare = currSquare + DOWN;
	
					if ( board[finalSquare] == EM ) {
	
						if ( squareMapping[ board120[finalSquare] ].at(1) == '1' ) {
							move = Move(currSquare, finalSquare, bb);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, bn);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, br);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, bq);
							addMove(move, moveList);
						}
		
						else {
							move = Move(currSquare, finalSquare);
							addMove(move, moveList);		
						}
					}

					finalSquare = currSquare + 2*DOWN;
	
					if ( board[finalSquare] != OB && board[finalSquare] == EM && squareMapping[ board120[currSquare] ].at(1) == '7' && board[finalSquare-DOWN] == EM ) {
						move = Move(currSquare, finalSquare);
						addMove(move, moveList);
					}
	
					finalSquare = currSquare + BOTTOM_LEFT;
	
					if ( board[finalSquare] != OB && board[finalSquare] != EM && pieceSide[ board[finalSquare] ] == white ) {
		
						if ( squareMapping[ board120[finalSquare] ].at(1) == '1' ) {
							move = Move(currSquare, finalSquare, bb);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, bn);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, br);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, bq);
							addMove(move, moveList);
						}
		
						else {
							move = Move(currSquare, finalSquare);
							addMove(move, moveList);		
						}
					}
	
					if ( enPassantSquare[black] != EM && finalSquare == enPassantSquare[black] && board[ enPassantSquare[black] ] == EM) {
						// in enPassant, we will set the square TO to empty due to the way we have coded playMove
						move = Move(currSquare);
						addMove(move, moveList);
					}
					 
					finalSquare = currSquare + BOTTOM_RIGHT;
	
					if ( board[finalSquare] != OB && board[finalSquare] != EM && pieceSide[ board[finalSquare] ] == white ) {
		
						if ( squareMapping[ board120[finalSquare] ].at(1) == '1' ) {
							move = Move(currSquare, finalSquare, bb);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, bn);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, br);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, bq);
							addMove(move, moveList);
						}
		
						else {
							move = Move(currSquare, finalSquare);
							addMove(move, moveList);		
						}
					}
	
					if ( enPassantSquare[black] != EM && finalSquare == enPassantSquare[black] && board[ enPassantSquare[black] ] == EM) {
						// in enPassant, we will set the square TO to empty due to the way we have coded playMove
						move = Move(currSquare);
						addMove(move, moveList);
					}
					break;
	
				case bn:
				case bk:
		
	
					for(int i = 0; i < pieceDirections[piece]; i++) {

						finalSquare = currSquare + moveArr[piece][i];
			
						if ( board[finalSquare] != OB && ( board[finalSquare] == EM || pieceSide[ board[finalSquare] ] == white ) ) {
							move = Move(currSquare, finalSquare);
							addMove(move, moveList);
						}
					}
					break;

				case bb:
				case br:
				case bq:
	
					for(int i = 0; i < pieceDirections[piece]; i++) {
						int increment = moveArr[piece][i];
						finalSquare = currSquare + increment;
		
						while ( board[finalSquare] != OB ) {
			
							if ( board[finalSquare] == EM ) {
								move = Move(currSquare, finalSquare);
								addMove(move, moveList);
								finalSquare += increment;
							}
			
							else if ( pieceSide[ board[finalSquare] ] == white ) {
								move = Move(currSquare, finalSquare);
								addMove(move, moveList);
								break;
							}
			
							else {
								break;
							}
						}
					}
					break;
				
					default: break;
				}
			}
		}
		
		// Now generate castle moves
		int castle = -1;
		bool isCastle = false;
		
		if ( blackCastlePerms[0] == true && board[f8] == EM && board[g8] == EM && board[e8] == bk && board[h8] == br ) {
			if ( isSquareSafe(e8, side) && isSquareSafe(g8, side) && isSquareSafe(f8, side) ) {
				isCastle = true;
				castle = 0;
				move = Move(isCastle, castle);
				addMove(move, moveList);
			}
		}
		
		if ( blackCastlePerms[1] == true && board[b8] == EM &&board[c8] == EM && board[d8] == EM && board[e8] == bk && board[a8] == br ){
			if ( isSquareSafe(e8, side) && isSquareSafe(c8, side) && isSquareSafe(d8, side) ) {
				isCastle = true;
				castle = 1;
				move = Move(isCastle, castle);
				addMove(move, moveList);
			}
		}
	}
}
