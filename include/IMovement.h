#pragma once

using Direction = std::pair<int, int>;

// Regular directions
const Direction up = { -1, 0 };
const Direction down = { 1, 0 };
const Direction left = { 0, -1 };
const Direction right = { 0, 1 };

// Diagonal directions
const Direction up_left = { -1, -1 };
const Direction up_right = { -1, 1 };
const Direction down_left = { 1, -1 };
const Direction down_right = { 1, 1 };

// Knight object directions
const Direction l_shaped_right_up = { -1, 2 };
const Direction l_shaped_left_up = { -1, -2 };

const Direction l_shaped_up_left = { -2, -1 };
const Direction l_shaped_up_right = { -2, 1 };

const Direction l_shaped_left_down = { 1, -2 };
const Direction l_shaped_right_down = { 1, 2 }; 

const Direction l_shaped_down_right = { 2, 1 };
const Direction l_shaped_down_left = { 2, -1 };

//An interface to implement a certain movement
class IMovement {
public:
	virtual bool canMoveInDirection(Direction) const = 0;
	virtual ~IMovement() {};
};

class HorizontalMovement : virtual public IMovement {
public:
	bool canMoveInDirection(Direction direction) const override {
		return direction == left || direction == right;
	};
};

class VerticalMovement : virtual public IMovement {
public:
	bool canMoveInDirection(Direction direction)const override {
		return direction == up || direction == down;
	};
};

class DiagonalMovement : virtual public IMovement {
public:
	bool canMoveInDirection(Direction direction)const override {
		return direction == up_left || direction == up_right ||
			direction == down_left || direction == down_right;
	};
};

class LShapedMove : virtual public IMovement {
public:
	bool canMoveInDirection(Direction direction)const override {
		return direction == l_shaped_up_right || direction == l_shaped_right_up ||
			direction == l_shaped_down_right || direction == l_shaped_right_down ||
			direction == l_shaped_up_left || direction == l_shaped_left_up ||
			direction == l_shaped_down_left || direction == l_shaped_left_down;
	};
};

class BidirectionalMovement : public HorizontalMovement, public VerticalMovement {
public:
	bool canMoveInDirection(Direction direction) const override {
		return HorizontalMovement::canMoveInDirection(direction) || VerticalMovement::canMoveInDirection(direction);
	}
};

class ForwardMovement : public DiagonalMovement, public VerticalMovement {
	Direction m_forwardDirection;
public:
	ForwardMovement(Direction forwardDirection) : m_forwardDirection(forwardDirection) {};
	bool canMoveInDirection(Direction direction) const override {
		if (m_forwardDirection == up) {
			return direction == up_left || direction == up_right || direction == up;
		}
		else {
			return direction == down_left || direction == down_right || direction == down;
		}
	};
};

class AllWayMovement : public HorizontalMovement, public VerticalMovement, public DiagonalMovement {
public:
	bool canMoveInDirection(Direction direction) const override {
		return HorizontalMovement::canMoveInDirection(direction) ||
			VerticalMovement::canMoveInDirection(direction) ||
			DiagonalMovement::canMoveInDirection(direction);
	}
};

