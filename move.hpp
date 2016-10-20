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
	Move(int init_pos, int final_pos, int *board);
	Move(int init_pos, int final_pos, int Promote, int *board);
	Move(bool iscastle, int castle);
	Move(bool isenPassant, int init_pos, int final_pos, int *board);
	Move(string move);
	
	void printMove(int side);
	string MoveToString(int side);

	bool isNull();
};

#endif
