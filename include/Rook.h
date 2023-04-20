#pragma once
#include "ChessPiece.h"

class Rook : public ChessPiece, public BidirectionalMovement{

public:

	Rook(const Color& color, const char rep, const Position& position) : ChessPiece(color, rep, position, MaxDistance::FullBoard) {};
};