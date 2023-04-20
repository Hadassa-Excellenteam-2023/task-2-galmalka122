#include "King.h"

bool King::isValidMove(const Direction dir, const int d) const
{
	return canMoveInDirection(dir) && d <= static_cast<int>(MaxDistance::OneSquare) ||
		DiagonalMovement::canMoveInDirection(dir) && d <= static_cast<int>(MaxDistance::TwoSquares);
}

King::King(Color color, char rep, const Position& position) : ChessPiece(color, rep, position, MaxDistance::OneSquare) {};

