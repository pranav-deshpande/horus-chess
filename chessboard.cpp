#include "chessboard.hpp"

// The chessboard class member functions

chessboard::chessboard() {
	initEmptyBoard();

	// The initial position of the board
	string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

	fenSetup(fen);
	initPieceList();
	initUniqueKey();
}

chessboard::chessboard(string &fen) {
	initEmptyBoard();
	
	fenSetup(fen);
	
	initPieceList();
	initUniqueKey();
}

void chessboard::initEmptyBoard() {
	
	// Initialize the board array
	for(int i = 0; i < BOARDSIZE; i++) {
		board[i] = OB;
	}
	
	for(int i = 0; i < 64; i++) {
		board[ board64[i] ] = EM;
	}

	// Now initialize the various variables which hold the board state
	for(int i = 0; i < 2; i++) {
		whiteCastlePerms[i] = false;
		blackCastlePerms[i] = false;
	}
	
	enPassantSquare[white] = enPassantSquare[black] = EM;
	
	plies = 0;
	moves = 1;
	fiftyMoveRule = 0;
	threeFold = 0;
	side = white; // default 
}

void chessboard::fenSetup(string &fen) {
	// Note that in this function, the validity of the fen string is not checked
	// So be careful
	int rank = rank8, file = fileA;
	int piece = 0, i;
	
	// Parse the first part, the arrangement of the pieces and set up the board accordingly
	for( i = 0; i < fen.length(); i++) {
	
		if ( fen[i] == ' ' ) {
			break;
		}
			
		else if ( fen[i] == '/' ) {
			rank--;
			file = fileA;
		}
		
		else if ( fen[i] >= '1' && fen[i] <= '8' ) {
			file += ( fen[i] - '0') ;
		}
		
		// Validity can be checked if we replace this else with if fen[i] in "pPnN..kK" and have another else block with error
		else {
			piece = reversePieceChars[ fen[i] ];
			int square = ( rank + 1 ) * 10 + file;
			board[square] = piece;
			file++;		
		}
	}

	side = ( fen[++i] == 'w' ) ? white : black;
	
	int j = ++i;
	int count = 0;
	while ( i++ < ( j + 4 ) ) {
		
		switch( fen[i] ) {
			
			case 'K': whiteCastlePerms[0] = true; break;
			case 'Q': whiteCastlePerms[1] = true; break;
			case 'k': blackCastlePerms[0] = true; break;
			case 'q': blackCastlePerms[1] = true; break;

		}
	}
	// Done thoughfully, don't worry
	if ( fen[++i] == '-' ) {
		i += 2;
	}

	else {
		string square = "";
		square = square + fen[i] + fen[i+1];
		enPassantSquare[side] = board64[ reverseSquareMapping[square] ];
		i += 3;
	}

	string num;
	int number;
	
	num = "";
	
	while ( isdigit( fen[i] ) ) {
		num = num + fen[i];
		i++;
	}
	
	number = atoi( num.c_str() );
	fiftyMoveRule = number;

	i++;
	num = "";
	
	while( isdigit( fen[i] ) ) {
		num = num + fen[i];
		i++;
	}

	number = atoi( num.c_str() );
	moves = number;
	plies = 0;
}

void chessboard::initPieceList() {
	// Initialize the piece list	
	for(int piece = wp; piece <= bk; piece++) {
		for(int square = 0; square < 64; square++) {
			if( piece == board[ board64[square] ] ) {
				pieceList[piece].insert( board64[square] );
			}
		}
	}
}

void chessboard::initUniqueKey() {
	
	// Generate the unique key
	uniqueKey = 0;

	for(int piece = wp; piece <= bk; piece++ ) {
		for(unordered_set<int>::iterator it = pieceList[piece].begin(); it != pieceList[piece].end(); it++) {
			uniqueKey ^= hashList[piece][ board120[*it] ];
		}
	}
	
	for(int i = 0; i < 2; i++) {
		if ( whiteCastlePerms[i] == true ) uniqueKey ^= whiteCastleHash[i];
		if ( blackCastlePerms[i] == true ) uniqueKey ^= blackCastleHash[i];
	}
	
	if ( enPassantSquare[side] != EM) uniqueKey ^= enPassantHash[ board120[ enPassantSquare[side] ] ];

	uniqueKey ^= sideHash[side];
}

void chessboard::playMove(Move &move) {

	// Move Generation is divided into 3 parts
	// Non castle non enPass Moves
	// EnPass Moves
	// Castling
	// First missing entries in move object are filled, 
	// then the board is updated, then the pieceList is updated and then the hash is updated
	
	// First store the castle history
	
	plies++;
	
	keyList.push_back(uniqueKey);
	
	array <bool, 4> castleWB;
	castleWB[0] = whiteCastlePerms[0];
	castleWB[1] = whiteCastlePerms[1];
	castleWB[2] = blackCastlePerms[0];
	castleWB[3] = blackCastlePerms[1];
	
	castleList.push_back(castleWB);
	
	pair <int, int> enPassSquares;
	enPassSquares.first = enPassantSquare[black];
	enPassSquares.second = enPassantSquare[white];
	
	enPassSqList.push_back(enPassSquares);
	
	if ( move.isEnPassant == true ) {
		
		move.currPiece = ( side == white ) ? wp : bp;
		move.capturedPiece = ( side == white ) ? bp : wp;  
		move.to = enPassantSquare[side];

		int squareOfCapturedPawn = ( side == white ) ? ( enPassantSquare[side] + DOWN ) : ( enPassantSquare[side] + UP );

		board[move.from] = EM;
		board[move.to] = move.currPiece;
		board[squareOfCapturedPawn] = EM;
		
		pieceList[move.currPiece].erase(move.from);
		pieceList[move.currPiece].insert(move.to);
		pieceList[move.capturedPiece].erase(squareOfCapturedPawn);
		
		uniqueKey ^= hashList[move.currPiece][ board120[move.from] ];
		uniqueKey ^= hashList[move.currPiece][ board120[move.to] ];
		uniqueKey ^= hashList[move.capturedPiece][ board120[squareOfCapturedPawn] ];

	}
	
	else if ( move.isCastle == true ) {
		
		if ( side == white ) {
		
			switch ( move.castle ) {
	
				case 0:
					board[e1] = board[h1] = EM;
					board[g1] = wk;
					board[f1] = wr;
			
					pieceList[wk].erase(e1);
					pieceList[wr].erase(h1);
					pieceList[wk].insert(g1);
					pieceList[wr].insert(f1);
			
					uniqueKey ^= hashList[wk][ board120[e1] ];
					uniqueKey ^= hashList[wr][ board120[h1] ];
					uniqueKey ^= hashList[wk][ board120[g1] ];
					uniqueKey ^= hashList[wr][ board120[f1] ];
					
					whiteCastlePerms[0] = whiteCastlePerms[1] = false;
					
					uniqueKey ^= whiteCastleHash[0];
					uniqueKey ^= whiteCastleHash[1];
			
					break;
	
				case 1:
					board[e1] = board[a1] = EM;
					board[c1] = wk;
					board[d1] = wr;
			
					pieceList[wk].erase(e1);
					pieceList[wr].erase(a1);
					pieceList[wk].insert(c1);
					pieceList[wr].insert(d1);
					
					uniqueKey ^= hashList[wk][ board120[e1] ];
					uniqueKey ^= hashList[wr][ board120[a1] ];
					uniqueKey ^= hashList[wk][ board120[c1] ];
					uniqueKey ^= hashList[wr][ board120[d1] ];
			
					whiteCastlePerms[0] = whiteCastlePerms[1] = false;
			
					uniqueKey ^= whiteCastleHash[0];
					uniqueKey ^= whiteCastleHash[1];
			
					break;
			}
		}	
		
		else {
		
			switch ( move.castle ) {
		
				case 0:
					board[e8] = board[h8] = EM;
					board[g8] = bk;
					board[f8] = br;
			
					pieceList[bk].erase(e8);
					pieceList[br].erase(h8);
					pieceList[bk].insert(g8);
					pieceList[br].insert(f8);
				
					uniqueKey ^= hashList[bk][ board120[e8] ];
					uniqueKey ^= hashList[br][ board120[h8] ];
					uniqueKey ^= hashList[bk][ board120[g8] ];
					uniqueKey ^= hashList[br][ board120[f8] ];
			
					blackCastlePerms[0] = blackCastlePerms[1] = false;
			
					uniqueKey ^= blackCastleHash[0];
					uniqueKey ^= blackCastleHash[1];
			
					break;
	
				case 1:
					board[e8] = board[a8] = EM;
					board[c8] = bk;
					board[d8] = br;
			
					pieceList[bk].erase(e8);
					pieceList[br].erase(a8);
					pieceList[bk].insert(c8);
					pieceList[br].insert(d8);
				
					uniqueKey ^= hashList[bk][ board120[e8] ];
					uniqueKey ^= hashList[br][ board120[a8] ];
					uniqueKey ^= hashList[bk][ board120[c8] ];
					uniqueKey ^= hashList[br][ board120[d8] ];
							
					blackCastlePerms[0] = blackCastlePerms[1] = false;
			
					uniqueKey ^= blackCastleHash[0];
					uniqueKey ^= blackCastleHash[1];
			
					break;
			}
		}
	}
	
	// Pawn Promotion move - thought of setting a boolean isPromoted but then it was unrequired after all
	
	else if ( move.promotedPiece != EM ) {
		
		move.currPiece = board[move.from];
		move.capturedPiece = board[move.to];
		
		board[move.from] = EM;
		board[move.to] = move.promotedPiece;
		
		pieceList[move.currPiece].erase(move.from);
		if ( move.capturedPiece != EM ) pieceList[move.capturedPiece].erase(move.to);
		pieceList[move.promotedPiece].insert(move.to);
		
		uniqueKey ^= hashList[move.currPiece][ board120[move.from] ];
		if ( move.capturedPiece != EM ) uniqueKey ^= hashList[move.capturedPiece][ board120[move.to] ];
		uniqueKey ^= hashList[move.promotedPiece][ board120[move.to] ];
	}
	
	else if ( move.promotedPiece == EM ){
	
		move.currPiece = board[move.from];
		move.capturedPiece = board[move.to];
		
		board[move.from] = EM;
		board[move.to] = move.currPiece;
		
		pieceList[move.currPiece].erase(move.from);
		if ( move.capturedPiece != EM ) pieceList[move.capturedPiece].erase(move.to);
		pieceList[move.currPiece].insert(move.to);
				
		uniqueKey ^= hashList[move.currPiece][ board120[move.from] ];
		if ( move.capturedPiece != EM ) uniqueKey ^= hashList[move.capturedPiece][ board120[move.to] ];
		uniqueKey ^= hashList[move.currPiece][ board120[move.to] ];
	
	}
	
	// Now all movements have been done, still some things are left
	// We have to check the castling permissions ( has the king/rook moved or is the rook captured? )
	// Also the enPassant square
		
	// Now first, Castling
	if ( whiteCastlePerms[0] == true ) {
		if ( ( move.currPiece == wk ) || ( move.currPiece == wr && move.from == h1 ) || ( board[h1] != wr ) || ( board[e1] != wk ) ) {
			whiteCastlePerms[0] = false;
			uniqueKey ^= whiteCastleHash[0];
		}
	}	
	
	if ( whiteCastlePerms[1] == true ) {
		if ( ( move.currPiece == wk ) || ( move.currPiece == wr && move.from == a1 ) || ( board[a1] != wr ) || ( board[e1] != wk ) ) {
			whiteCastlePerms[1] = false;
			uniqueKey ^= whiteCastleHash[1];
		}
	}
	
	if ( blackCastlePerms[0] == true ) {
		if ( ( move.currPiece == bk ) || ( move.currPiece == br && move.from == h8 ) || ( board[h8] != br ) || ( board[e8] != bk ) ) {
			blackCastlePerms[0] = false;
			uniqueKey ^= blackCastleHash[0];
		}
	}
	
	if ( blackCastlePerms[1] == true ) {
		if ( ( move.currPiece == bk ) || ( move.currPiece == br && move.from == a8 ) || ( board[a8] != br ) || ( board[e8] != bk ) ) {
			blackCastlePerms[1] = false;
			uniqueKey ^= blackCastleHash[1];
		}
	}
		
	// Second - EnPassant
	enPassantSquare[side] = EM; // Now it's done, from the next move onwards it will not be an enPassant Square
	
	// Setting the enPassant for the next ply, only set if a pawn has moved two squares
	
	int pawn = ( side == white ) ? wp : bp;
	int increment = ( side == white ) ? 2*UP : 2*DOWN;	
	
	if ( move.currPiece == pawn && ( move.to == move.from + increment ) ) {
		
		enPassantSquare[!side] = move.from + increment/2;
	
		uniqueKey ^= enPassantHash[ board120[ enPassantSquare[!side] ] ];
	
	}
	
	uniqueKey ^= sideHash[side];
	uniqueKey ^= sideHash[!side];
	
	side = !side;
}

void chessboard::undoMove(Move &move) {
	
	if ( move.isEnPassant == true ) {
	
		int squareOfCapturedPawn = ( !side == white ) ? ( move.to + DOWN ) : ( move.to + UP ); 

		board[move.to] = EM;
		board[move.from] = move.currPiece;
		board[squareOfCapturedPawn] = move.capturedPiece;
		
		pieceList[move.currPiece].erase(move.to);
		pieceList[move.currPiece].insert(move.from);
		pieceList[move.capturedPiece].insert(squareOfCapturedPawn);

	}
	
	else if ( move.isCastle == true ) {
	
		if ( !side == white ) {
			
			switch ( move.castle ) {
			
				case 0:
					board[g1] = board[f1] = EM;
					board[e1] = wk;
					board[h1] = wr;
					
					pieceList[wk].erase(g1);
					pieceList[wr].erase(f1);
					pieceList[wk].insert(e1);
					pieceList[wr].insert(h1);
					
					break;
					
				case 1:
					board[c1] = board[d1] = EM;
					board[e1] = wk;
					board[a1] = wr;
					
					pieceList[wk].erase(c1);
					pieceList[wr].erase(d1);
					pieceList[wk].insert(e1);
					pieceList[wr].insert(a1);
			
					break;
			}
		}
		
		else {
			
			switch ( move.castle ) {
			
				case 0:
					board[g8] = board[f8] = EM;
					board[e8] = bk;
					board[h8] = br;
					
					pieceList[bk].erase(g8);
					pieceList[br].erase(f8);
					pieceList[bk].insert(e8);
					pieceList[br].insert(h8);
					
					break;
					
				case 1:
					board[c8] = board[d8] = EM;
					board[e8] = bk;
					board[a8] = br;
					
					pieceList[bk].erase(c8);
					pieceList[br].erase(d8);
					pieceList[bk].insert(e8);
					pieceList[br].insert(a8);
	
					break;
			}
		}
	}
	
	else if ( move.promotedPiece != EM ) {
		
		board[move.to] = move.capturedPiece;
		board[move.from] = move.currPiece;
		
		pieceList[move.promotedPiece].erase(move.to);
		if ( move.capturedPiece != EM ) pieceList[move.capturedPiece].insert(move.to);
		pieceList[move.currPiece].insert(move.from);

	}
	
	else {
		
		board[move.to] = move.capturedPiece;
		board[move.from] = move.currPiece;
		
		pieceList[move.currPiece].erase(move.to);		
		if ( move.capturedPiece != EM ) pieceList[move.capturedPiece].insert(move.to);
		pieceList[move.currPiece].insert(move.from);

	}

	plies--;

	whiteCastlePerms[0] = castleList[plies][0];
	whiteCastlePerms[1] = castleList[plies][1];
	blackCastlePerms[0] = castleList[plies][2];
	blackCastlePerms[1] = castleList[plies][3];
	enPassantSquare[black] = enPassSqList[plies].first;
	enPassantSquare[white] = enPassSqList[plies].second;
	
	uniqueKey = keyList[plies];
	keyList.pop_back();
	enPassSqList.pop_back();
	castleList.pop_back();

			
	side = !side;
}

bool chessboard::isSquareAttacked(int square, int Side) {

	int kMoves[] = {UP, DOWN, RIGHT, LEFT, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};
	int nMoves[] = {NM1, NM2, NM3, NM4, NM5, NM6, NM7, NM8};
	int straightMoves[] = {UP, DOWN, RIGHT, LEFT};
	int diagMoves[] = {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT};	
	int increment, finalSquare;
	
	if ( Side == white ) {
		
		if ( board[square+TOP_LEFT] == bp || board[square+TOP_RIGHT] == bp ) {
			return true;
		}
				
		for(int i = 0; i < 8; i++) {
			if ( board[ square + nMoves[i] ] == bn ) {
				return true;
			}
		}

		for(int i = 0; i < 8; i++) {
			if ( board[ square + kMoves[i] ] == bk ) {
				return true;
			}
		}
		
		for(int i = 0; i < 4; i++) {
			increment = straightMoves[i];
			finalSquare = square + increment;
			
			while ( board[finalSquare] != OB ) {
				
				if ( board[finalSquare] == bq || board[finalSquare] == br ) {
					return true;
				}
				
				else if ( board[finalSquare] == EM ) {
					finalSquare += increment;
				}
				
				else break;	// implies another black piece or white piece is there
			}
		}
		
		for(int i = 0; i < 4; i++) {
			increment = diagMoves[i];
			finalSquare = square + increment;
			
			while ( board[finalSquare] != OB ) {
				
				if ( board[finalSquare] == bq || board[finalSquare] == bb ) {
					return true;
				}
				
				else if ( board[finalSquare] == EM ) {
					finalSquare += increment;
				}
				
				else break; // implies another black piece or white piece is there		
			}
		}
	}
	
	else {
	
		if ( board[square + BOTTOM_LEFT] == wp || board[square + BOTTOM_RIGHT] == wp )
			return true;
			
		for(int i = 0; i < 8; i++) {
			if ( board[ square + nMoves[i] ] == wn )
				return true;		
		}
		
		for(int i = 0; i < 8; i++) {
			if ( board[ square + kMoves[i] ] == wk )
				return true;
		}
			
		for(int i = 0; i < 4; i++) {
			increment = straightMoves[i];
			finalSquare = square + increment;
			
			while ( board[finalSquare] != OB ) {
				
				if ( board[finalSquare] == wq || board[finalSquare] == wr )
					return true;
				
				else if ( board[finalSquare] == EM ) {
					finalSquare += increment;
				}
				
				else break;	// implies another black piece or white piece is there
			}
		}
		
		for(int i = 0; i < 4; i++) {
			increment = diagMoves[i];
			finalSquare = square + increment;
			
			while ( board[finalSquare] != OB ) {
				
				if ( board[finalSquare] == wq || board[finalSquare] == wb )
					return true;
				
				else if ( board[finalSquare] == EM ) {
					finalSquare += increment;
				}
				
				else break; // implies another black piece or white piece is there		
			}
		}
	}

	return false;
}				
	
bool chessboard::isSquareSafe(int square, int Side) {
	return !isSquareAttacked(square, Side);
}

bool chessboard::isMoveValid(Move &move) {
	
	bool validity;
	int sideToBeChecked = side;
	int king = ( sideToBeChecked == white ) ? wk : bk;
	int kingSquare;
	
	playMove(move);
	
	kingSquare = *( pieceList[king].begin() );
	
	if ( isSquareSafe(kingSquare, sideToBeChecked) ) {
		validity = true;
	}
	
	else validity = false;
	
	undoMove(move);

	return validity;
}

void chessboard::addMove(Move &move, vector<Move> &moveList) {
	if ( isMoveValid(move) )
		moveList.push_back(move);
}

Move chessboard::parseMoveFromString(string move) {
	// Note that this function does not check if the move input is valid!
	// So be careful in the console mode. However, xboard does check for move validity
	Move m;
	
	if (move == "e1g1" || move == "e1c1" || move == "e8g8" || move == "e8c8") {
		
		if ( move == "e1g1" || move == "e8g8" ) {
			m = Move(true, 0);
		}
		
		else {
			m = Move(true, 1);
		}
	}
	
	else {
		int From = board64[ reverseSquareMapping[ move.substr(0,2) ] ];
		int To = board64[ reverseSquareMapping[ move.substr(2, 4) ] ];
		int pawn = ( side == white ) ? wp : bp;
		
		if ( move.length() == 5 ) {
			int PromotedPiece = reversePieceChars[ move[4] ];
			m = Move(From, To, PromotedPiece);
		}
		
		else if ( board[From] == pawn && board[To] == enPassantSquare[side] && board[To] == EM ) {
			m = Move(From);
		}
	
		else {
			m = Move(From, To);
		}
	}
	
	return m;
}

// Thanks to Sven Schüle of talkchess.com for this routine which is helpful while debugging
// It checks whether the present state of the chessboard is valid or not
bool chessboard::isValid() {
	static int const MinPieces[1+12] = { 0, 0,   0,   0,   0,   0, 1, 0,   0,   0,   0,   0, 1 };
	static int const MaxPieces[1+12] = { 0, 8, 2+8, 2+8, 2+8, 1+8, 1, 8, 2+8, 2+8, 2+8, 1+8, 1 };

	for (int piece = wp; piece <= bk; piece++) {
		
		if (pieceList[piece].size() < MinPieces[piece]) {
			cerr << "less pieces of type " << piece << " than allowed minimum" << endl;
			flush(cerr);
			return false;
		}
		
		if (pieceList[piece].size() > MaxPieces[piece]) {
			cerr << "more pieces of type " << piece << " than allowed maximum" << endl;
			flush(cerr);
			return false;
		}
		
		for(unordered_set<int>::iterator it = pieceList[piece].begin(); it != pieceList[piece].end(); it++) {
			if (board[*it] != piece) {
				cerr << "piece list of type " << piece << " contains square " << *it;
				cerr << " but board contains " << board[*it] << " at that square" << endl;
				flush(cerr);
				return false;
			}
		}
	}
	
	for (int square = 0; square < 64; square++) {
		int sq = board64[square];
		int piece = board[sq];
		
		if (piece != EM) {
		
			if (piece < wp || piece > bk) {
				cerr << "illegal piece " << piece << " on square " << sq << endl;
				flush(cerr);
				return false;
			}
		
			if (pieceList[piece].find(sq) == pieceList[piece].end()) {
				cerr << "piece list of type " << piece << " that was found on square " << sq << " does not contain that square" << endl;
				flush(cerr);
				return false;
			}
		}	
	}
	
	return true;
}

// Print just the board - useful with debugPerft later
void chessboard::printMinimalBoard() {
	cout << "-----------------------------------------------" << endl;
	cout << "Current Postion:\n";
	
	int square;
	for(int rank = rank8; rank >= rank1; rank--) {
		putchar('\n');
		printf("%c", rank + '1' - 1);
		for(int file = fileA; file <= fileH; file++) {
			square = (rank+1) * 10 + file;
			printf("%3c", pieceChars[ board[square] ]);
		}
	}
	cout << "\n\n ";
	for(int i = 0; i < 8; i++) {
		printf("%3c", 'a' + i);
	}
	
	cout << "\n\n";
	
	cout << "Side to move: ";
	if(side == white) cout << "White" << endl;
	else cout << "Black" << endl;
	
	cout << "-----------------------------------------------" << endl;
}
	
// Detailed description of the board - This helped me a lot while debugging
void chessboard::printBoard() {
	cout << "-----------------------------------------------" << endl;
	cout << "Current Postion:\n";
	
	int square;
	for(int rank = rank8; rank >= rank1; rank--) {
		putchar('\n');
		printf("%c", rank + '1' - 1);
		for(int file = fileA; file <= fileH; file++) {
			square = (rank+1) * 10 + file;
			printf("%3c", pieceChars[ board[square] ]);
		}
	}
	cout << "\n\n ";
	for(int i = 0; i < 8; i++) {
		printf("%3c", 'a' + i);
	}
	
	cout << "\n\n";
	
	cout << "Side to move: ";
	if(side == white) cout << "White" << endl;
	else cout << "Black" << endl;
	
	cout << "Castle Permissions(white - KQ): ";
	for(int i = 0; i < 2; i++) {
		cout << whiteCastlePerms[i];
	}
	
	cout << '\n';
	
	cout << "Castle Permissions(black - kq): ";
	for(int i = 0; i < 2; i++) {
		cout << blackCastlePerms[i];
	}
	
	cout << '\n';
	
	int enPassSquare = board120[ enPassantSquare[side] ];
		 
	if ( enPassSquare >= board120[a1] && enPassSquare <= board120[h8] )
		cout << "\nEnPassant Square: " << squareMapping[enPassSquare] << endl;
	
	else 
		cout << "No Valid EnPassant Square is present." << endl;
	
	cout << "\nPiece List:\n\n";
	
	int piecesCount = 0;

	for(int piece = wp; piece <= bk; piece++) {
		cout << pieceChars[piece] << ": ";
		piecesCount += pieceList[piece].size();
		for(unordered_set<int>::iterator it = pieceList[piece].begin(); it != pieceList[piece].end(); it++ ) {
			cout << squareMapping[ board120[ *it ] ] << " ";
		}
		cout << endl;
	}
	
	cout << "\nCount of pieces: " << piecesCount << endl;
	
	vector <Move> moveList;
	generateAllMoves(moveList);
	
	cout << "No. of possible(legal) moves: " << moveList.size() << endl << endl;
	for(vector<Move>::iterator it = moveList.begin(); it != moveList.end(); it++) {
		(*it).printMove(side);
		cout << endl;
	}
	
	cout << endl;
	moveList.clear();
	
	cout << "No. of plies till now: " << plies << endl;
	cout << "No. of moves till now: " << moves << endl;
	cout << "Fifty Move Rule: " << fiftyMoveRule << endl;
	cout << "Three Fold Repetition: " << threeFold << endl << endl;
	cout << "Unique Postion Key: " << uniqueKey << endl;
	cout << "-----------------------------------------------" << endl;
}
