#include "Pawn.h"

Pawn::Pawn(Color color, char rep, const Position& position) : ChessPiece(color, rep, position, MaxDistance::TwoSquares),
ForwardMovement(color == White ? down : up) {}

bool Pawn::isValidMove(const Direction direction, const int d) const
{

	if (ForwardMovement::canMoveInDirection(direction) && d <= static_cast<int>(MaxDistance::OneSquare)) {
		return true;
	}

	if (d == static_cast<int>(MaxDistance::TwoSquares) && DiagonalMovement::canMoveInDirection(direction)) {
		return true;
	}
	return false;
}

bool Pawn::canColide(const ChessPiece& other, const Direction d, const bool dest) const {
	if (&other && (dest && DiagonalMovement::canMoveInDirection(d) && getColor() != other.getColor()))
		return true;
	if (!&other && VerticalMovement::canMoveInDirection(d))
		return true;
	return false;
}

