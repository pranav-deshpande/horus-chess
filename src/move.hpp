/*
Horus - A Chess Engine created for learning Game AI techniques
Copyright (C) 2016 Pranav Deshpande

This file is a part of Horus.

Horus is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

Horus is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Horus. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __MOVE__
#define __MOVE__

#include "data.hpp"

class Move {
public:
	int8_t from, to;
	int8_t currPiece, capturedPiece, promotedPiece;
	int8_t castle;
	bool isCastle, isEnPassant;
	int score = 0;

	Move();
	Move(int init_pos, int final_pos, int currpiece, int capturedpiece);
	Move(int init_pos, int final_pos, int currpiece, int capturedpiece, int Promote);
	Move(bool iscastle, int castle);
	Move(bool isenPassant, int init_pos, int final_pos, int currpiec, int capturedpiece);

	string MoveToString() const;

	bool isNull() const;
};

#endif
