#pragma once
#include "ChessPiece.h"

class Bishop : public ChessPiece, public DiagonalMovement {

public:

	Bishop(Color color, char rep, const Position& position) : ChessPiece(color, rep, position, MaxDistance::FullBoard) {};

};