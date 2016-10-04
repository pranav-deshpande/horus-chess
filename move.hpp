#ifndef __MOVE__
#define __MOVE__

#include "data.hpp"

class Move {
public:
	int from, to;
	int currPiece, capturedPiece, promotedPiece;
	int castle;
	bool isCastle, isEnPassant;
	
	Move();
	Move(int init_pos, int final_pos);
	Move(int init_pos, int final_pos, int Promote);
	Move(bool iscastle, int castle);
	Move(int init_pos);
	Move(string move);
	
	void printMove();
	
};

#endif
