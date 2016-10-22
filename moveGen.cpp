#include "chessboard.hpp"

void chessboard::generateAllMoves(vector <Move> &moveList) {

#ifndef NDEBUG
	suppressValidityCheck = true;
#endif /* NDEBUG */

	pins = getPins();
	inCheck = isSquareAttacked(kingSquare(side), side);

	moveList.clear();
	
	static int const pieceSide[] = { empty, white, white, white, white, white, white, black, black, black, black, black, black };
	static int const pieceDirections[] = {EM, EM, 8, 4, 4, 8, 8, EM, 8, 4, 4, 8, 8};

	static int const moveArr[13][8] = {
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
							move = Move(currSquare, finalSquare, piece, board[finalSquare], wb);
							addMove(move, moveList);
					
							move = Move(currSquare, finalSquare, piece, board[finalSquare], wn);
							addMove(move, moveList);
					
							move = Move(currSquare, finalSquare, piece, board[finalSquare], wr);
							addMove(move, moveList);
					
							move = Move(currSquare, finalSquare, piece, board[finalSquare], wq);
							addMove(move, moveList);
						}
				
						else {
							move = Move(currSquare, finalSquare, piece, board[finalSquare]);
							addMove(move, moveList);		
						}
					}
		
					// --------------------------
					// pawn double step
					// --------------------------
					finalSquare = currSquare + 2*UP;
			
					if ( board[finalSquare] == EM && board[finalSquare-UP] == EM && squareMapping[ board120[currSquare] ].at(1) == '2' ) {
						move = Move(currSquare, finalSquare, piece, board[finalSquare]);
						addMove(move, moveList);
					}
			
					// --------------------------
					// pawn capture to left side
					// --------------------------
					finalSquare = currSquare + TOP_LEFT;
			
					if ( board[finalSquare] != OB && pieceSide[ board[finalSquare] ] == black ) {
				
						ASSERT(board[finalSquare] != EM);
						if ( squareMapping[ board120[finalSquare] ].at(1) == '8' ) {
							move = Move(currSquare, finalSquare, piece, board[finalSquare], wb);
							addMove(move, moveList);
					
							move = Move(currSquare, finalSquare, piece, board[finalSquare], wn);
							addMove(move, moveList);
					
							move = Move(currSquare, finalSquare, piece, board[finalSquare], wr);
							addMove(move, moveList);
					
							move = Move(currSquare, finalSquare, piece, board[finalSquare], wq);
							addMove(move, moveList);
						}
				
						else {
							move = Move(currSquare, finalSquare, piece, board[finalSquare]);
							addMove(move, moveList);		
						}
					}
			
					// --------------------------
					// ep capture to left side
					// --------------------------
					if ( finalSquare == enPassantSquare[white] && board[ enPassantSquare[white] ] == EM ) {
						move = Move(true, currSquare, finalSquare, piece, bp);
						addMove(move, moveList);
					}
					 
					// --------------------------
					// pawn capture to right side
					// --------------------------
					finalSquare = currSquare + TOP_RIGHT;
			
					if ( board[finalSquare] != OB && pieceSide[ board[finalSquare] ] == black ) {

						ASSERT(board[finalSquare] != EM);
						if ( squareMapping[ board120[finalSquare] ].at(1) == '8' ) {
							move = Move(currSquare, finalSquare, piece, board[finalSquare], wb);
							addMove(move, moveList);
					
							move = Move(currSquare, finalSquare, piece, board[finalSquare], wn);
							addMove(move, moveList);
					
							move = Move(currSquare, finalSquare, piece, board[finalSquare], wr);
							addMove(move, moveList);
					
							move = Move(currSquare, finalSquare, piece, board[finalSquare], wq);
							addMove(move, moveList);
						}
				
						else {
							move = Move(currSquare, finalSquare, piece, board[finalSquare]);
							addMove(move, moveList);		
						}
					}
			
					// --------------------------
					// ep capture to right side
					// --------------------------
					if ( finalSquare == enPassantSquare[white] && board[ enPassantSquare[white] ] == EM) {
						move = Move(true, currSquare, finalSquare, piece, bp);
						addMove(move, moveList);
					}
					break;
			
				case wn:
				case wk:
					for(int i = 0; i < pieceDirections[piece]; i++) {
						finalSquare = currSquare + moveArr[piece][i];
			
						if ( board[finalSquare] != OB && ( board[finalSquare] == EM || pieceSide[ board[finalSquare] ] == black ) ) {
							move = Move(currSquare, finalSquare, piece, board[finalSquare]);
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
								move = Move(currSquare, finalSquare, piece, board[finalSquare]);
								addMove(move, moveList);
								finalSquare += increment;
							}
					
							else if ( pieceSide[ board[finalSquare] ] == black ) {
								move = Move(currSquare, finalSquare, piece, board[finalSquare]);
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

		if ( whiteCastlePerms[0] ) {

			ASSERT(board[e1] == wk);
			ASSERT(board[h1] == wr);

			if ( !inCheck
			  && board[f1] == EM && board[g1] == EM
			  && isSquareSafe(f1, side) && isSquareSafe(g1, side) ) {

				move = Move(true, wOO);
				addMove(move, moveList);
			}
		}
	
		if ( whiteCastlePerms[1] ) {

			ASSERT(board[e1] == wk);
			ASSERT(board[a1] == wr);

			if ( !inCheck
			  && board[d1] == EM && board[c1] == EM && board[b1] == EM
			  && isSquareSafe(d1, side) && isSquareSafe(c1, side) ) {

				move = Move(true, wOOO);
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
					// --------------------------
					// pawn single step
					// --------------------------
					finalSquare = currSquare + DOWN;
	
					if ( board[finalSquare] == EM ) {
	
						if ( squareMapping[ board120[finalSquare] ].at(1) == '1' ) {
							move = Move(currSquare, finalSquare, piece, board[finalSquare], bb);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, piece, board[finalSquare], bn);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, piece, board[finalSquare], br);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, piece, board[finalSquare], bq);
							addMove(move, moveList);
						}
		
						else {
							move = Move(currSquare, finalSquare, piece, board[finalSquare]);
							addMove(move, moveList);		
						}
					}

					// --------------------------
					// pawn double step
					// --------------------------
					finalSquare = currSquare + 2*DOWN;
	
					if ( board[finalSquare] == EM && squareMapping[ board120[currSquare] ].at(1) == '7' && board[finalSquare-DOWN] == EM ) {
						move = Move(currSquare, finalSquare, piece, board[finalSquare]);
						addMove(move, moveList);
					}
	
					// --------------------------
					// pawn capture to left side
					// --------------------------
					finalSquare = currSquare + BOTTOM_LEFT;
	
					if ( board[finalSquare] != OB && pieceSide[ board[finalSquare] ] == white ) {

						ASSERT(board[finalSquare] != EM);
						if ( squareMapping[ board120[finalSquare] ].at(1) == '1' ) {
							move = Move(currSquare, finalSquare, piece, board[finalSquare], bb);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, piece, board[finalSquare], bn);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, piece, board[finalSquare], br);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, piece, board[finalSquare], bq);
							addMove(move, moveList);
						}
		
						else {
							move = Move(currSquare, finalSquare, piece, board[finalSquare]);
							addMove(move, moveList);		
						}
					}
	
					// --------------------------
					// ep capture to left side
					// --------------------------
					if ( finalSquare == enPassantSquare[black] && board[ enPassantSquare[black] ] == EM) {
						move = Move(true, currSquare, finalSquare, piece, wp);
						addMove(move, moveList);
					}
					 
					// --------------------------
					// pawn capture to right side
					// --------------------------
					finalSquare = currSquare + BOTTOM_RIGHT;
	
					if ( board[finalSquare] != OB && pieceSide[ board[finalSquare] ] == white ) {

						ASSERT(board[finalSquare] != EM);
						if ( squareMapping[ board120[finalSquare] ].at(1) == '1' ) {
							move = Move(currSquare, finalSquare, piece, board[finalSquare], bb);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, piece, board[finalSquare], bn);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, piece, board[finalSquare], br);
							addMove(move, moveList);
			
							move = Move(currSquare, finalSquare, piece, board[finalSquare], bq);
							addMove(move, moveList);
						}
		
						else {
							move = Move(currSquare, finalSquare, piece, board[finalSquare]);
							addMove(move, moveList);		
						}
					}
	
					// --------------------------
					// ep capture to right side
					// --------------------------
					if ( finalSquare == enPassantSquare[black] && board[ enPassantSquare[black] ] == EM) {
						move = Move(true, currSquare, finalSquare, piece, wp);
						addMove(move, moveList);
					}
					break;
	
				case bn:
				case bk:
		
	
					for(int i = 0; i < pieceDirections[piece]; i++) {

						finalSquare = currSquare + moveArr[piece][i];
			
						if ( board[finalSquare] != OB && ( board[finalSquare] == EM || pieceSide[ board[finalSquare] ] == white ) ) {
							move = Move(currSquare, finalSquare, piece, board[finalSquare]);
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
								move = Move(currSquare, finalSquare, piece, board[finalSquare]);
								addMove(move, moveList);
								finalSquare += increment;
							}
			
							else if ( pieceSide[ board[finalSquare] ] == white ) {
								move = Move(currSquare, finalSquare, piece, board[finalSquare]);
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

		if ( blackCastlePerms[0] ) {

			ASSERT(board[e8] == bk);
			ASSERT(board[h8] == br);

			if ( !inCheck
			  && board[f8] == EM && board[g8] == EM
			  && isSquareSafe(f8, side) && isSquareSafe(g8, side) ) {

				move = Move(true, bOO);
				addMove(move, moveList);
			}
		}
		
		if ( blackCastlePerms[1] ) {

			ASSERT(board[e8] == bk);
			ASSERT(board[a8] == br);

			if ( !inCheck
			  && board[d8] == EM && board[c8] == EM && board[b8] == EM
			  && isSquareSafe(d8, side) && isSquareSafe(c8, side) ) {
				move = Move(true, bOOO);
				addMove(move, moveList);
			}
		}
	}

#ifndef NDEBUG
	suppressValidityCheck = false;
#endif /* NDEBUG */

}
