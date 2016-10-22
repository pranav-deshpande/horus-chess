#ifndef __MOVE__
#define __MOVE__

#include "data.hpp"

class Move {
public:
	int8_t from, to;
	int8_t currPiece, capturedPiece, promotedPiece;
	int8_t castle;
	bool isCastle, isEnPassant;
	int16_t score;
	
	Move();
	Move(int init_pos, int final_pos, int currpiece, int capturedpiece);
	Move(int init_pos, int final_pos, int currpiece, int capturedpiece, int Promote);
	Move(bool iscastle, int castle);
	Move(bool isenPassant, int init_pos, int final_pos, int currpiece, int capturedpiece);
	
	string MoveToString() const;

	bool isNull() const;
};

#endif
