#pragma once
#include "ChessPiece.h"

class King : public ChessPiece, public AllWayMovement {

	
public:
	bool isValidMove(const Direction, const int) const override;
	King(Color color, char rep, const Position& position);
	
};