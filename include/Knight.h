#pragma once
#include "ChessPiece.h"

class Knight : public ChessPiece, public LShapedMove {
	
public:
	bool canColide(const ChessPiece&, const Direction, const bool) const override;
	bool isValidMove(const Direction, const int) const override;
	Knight(Color color, char rep, const Position& position);

};