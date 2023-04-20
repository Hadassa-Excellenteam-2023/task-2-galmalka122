#include "ChessPiece.h"

ChessPiece::ChessPiece(Color color, char rep, const Position& position, MaxDistance max) :
	m_color(color), m_maxSquares(max), m_rep(rep), m_position(position) {};

// Check if a piece can colide with another piece (or empty square)
bool ChessPiece::canColide(const ChessPiece& other, const Direction d, const bool dest) const {
	if (&other && (m_color == other.m_color || !dest))
		return false;

	return true;
}

bool ChessPiece::isValidMove(const Direction dir, const int d) const {
	return canMoveInDirection(dir) && abs(d) <= static_cast<int>(m_maxSquares);
};

void ChessPiece::move(const Position& position) { m_position = position; };

const Color ChessPiece::getColor() const { return m_color; };

const Position& ChessPiece::getPosition() const { return m_position; };

const char ChessPiece::getRep() const { return m_rep; };