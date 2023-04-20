#pragma once
#include "ChessPiece.h"

class Queen : public ChessPiece, public AllWayMovement {
public:

	Queen(Color color, char rep, const Position& position) : ChessPiece(color, rep, position, MaxDistance::FullBoard) {};

};