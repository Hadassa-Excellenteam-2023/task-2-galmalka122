#pragma once
#include "ChessPiece.h"

class Pawn: public ChessPiece, public ForwardMovement {
private:

public:

	Pawn(Color, char, const Position&);
	bool isValidMove(const Direction, const int) const override;
	bool canColide(const ChessPiece&, const Direction, const bool) const override;
};