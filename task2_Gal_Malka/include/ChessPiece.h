#pragma once
#include "Position.h"

enum Color : bool
{
	White = true,
	Black = false
};

enum class MaxDistance {
	OneSquare = 1,
	TwoSquares,
	ThreeSquares,
	FullBoard = 18
};

class ChessPiece : public virtual IMovement{
private:

	Position m_position;
	Color m_color;
	MaxDistance m_maxSquares;
	char m_rep;

public:

	ChessPiece(Color, char, const Position&, const MaxDistance);
	virtual void move(const Position&);
	virtual bool canColide(const ChessPiece&, const Direction, const bool) const;
	virtual bool isValidMove(const Direction dir, const int d) const;
	const Position& getPosition() const;
	const Color getColor() const;
	const char getRep() const;
	virtual ~ChessPiece() = default;
};