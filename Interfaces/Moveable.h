#pragma once

#include <GL/glew.h>

#include "../../Utils/PhysicalUnitVec.h"

class Moveable {
public:
	Moveable(const PhysicalUnitVec<3>& position)
		: position(position)
		, canMove(true) {};

	virtual ~Moveable() {}
	void moveBy(const PhysicalUnitVec<3>& position) { this->position += position; }
	void setPosition(const PhysicalUnitVec<3>& position) { this->position = position; }
	void setCanMove(bool canMove) { this->canMove = canMove; }

	PhysicalUnitVec<3> getPosition() const { return position; }
	bool getCanMove() const { return canMove; }

protected:
	PhysicalUnitVec<3> position;
	bool canMove;
};