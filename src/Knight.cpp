#include"Knight.h"

Knight::Knight(Color color, char rep, const Position& position) : ChessPiece(color, rep, position, MaxDistance::ThreeSquares) {}

bool Knight::canColide(const ChessPiece& other, const Direction d, const bool dest) const
{
	if ((dest && &other) && (getColor() == other.getColor()))
		return false;

	return true;

}

bool Knight::isValidMove(const Direction dir, const int d) const
{
	return canMoveInDirection(dir) && static_cast<int>(MaxDistance::ThreeSquares) == d;
}

