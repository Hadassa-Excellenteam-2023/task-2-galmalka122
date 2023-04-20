#include "Position.h"

Position::Position(const string& position){ 
	row = int(position[0] - 'a');
	col = int(position[1] - '1'); 
}

Position::Position(const int row, const int col) { 
	this->row = row; 
	this->col = col; 
}

Position::Position(const Position& other) { 
	row = other.row;
	col = other.col; 
}

Position::Position(Position&& other) noexcept { 
	row = other.row; 
	col = other.col; 
}

Position Position::operator+(Direction& direction) { 
	row += direction.first; 
	col += direction.second; 
	return *this; 
}

Position& Position::operator+=(Direction& direction) { 
	*this = *this + direction; 
	return *this; 
}

Position Position::operator=(const Position& other) { 
	row = other.row; 
	col = other.col; 
	return *this; 
}

const string& Position::toString() const { 
	return string() + char('a' - row) + char(col); 
}

const bool Position::operator==(const Position& other) const {
	return row == other.row && col == other.col;
}

const bool Position::operator!=(const Position& other) const {
	return !(*this == other);
}

const bool Position::inRange(const int height, const int width) const { 
	return (0 <= row && row < height) && (0 <= col && col < width); 
}

const int Position::getDistance(const Position& other) const {
	return abs(other.row - row) + abs(other.col - col);
}

const Direction Position::getDirection(const Position& other) const {

	int d_row = other.row - row, d_col = other.col - col;

	if (d_row != 0 && d_col == 0) d_row = d_row / abs(d_row);

	else if (d_row == 0 && d_col != 0) d_col = d_col / abs(d_col);

	else if (abs(d_row) == abs(d_col)) {
		d_row = d_row / abs(d_row);
		d_col = d_col / abs(d_col);
	}

	return {d_row,d_col};
}