#pragma once
#include <string>
#include <vector>
#include "IMovement.h"

using std::string;
using std::vector;

using Distance = std::pair<int, int>;

//Represents a chess piece position on the board
struct Position {

	int row;
	int col;

	Position(const string& position);
	Position(const int row, const int col);
	Position(const Position& other);
	Position(Position&& other) noexcept;

	Position operator+(Direction& direction);
	Position& operator+=(Direction& direction);
	Position operator=(const Position& other);

	const string& toString() const;
	const bool operator==(const Position& other) const;
	const bool operator!=(const Position& other) const;
	const bool inRange(const int height, const int width) const;
	const int getDistance(const Position& other) const;
	const Direction getDirection(const Position& other) const;

};