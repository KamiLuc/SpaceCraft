#pragma once

#include <GL/glew.h>
#include <glm/ext/vector_float3.hpp>

#include "../../Utils/Measure.h"

class Moveable {
public:
	Moveable(const Measure<3>& position)
		: position(position)
		, canMove(false) {};

	virtual ~Moveable() {}
	void moveBy(const Measure<3>& position) { this->position += position; }
	void setPosition(const Measure<3>& position) { this->position = position; }
	void setPosition(const glm::vec3 position, int exponent) {
		this->position = Measure<3>(position, exponent);
	}
	void setCanMove(bool canMove) { this->canMove = canMove; }

	Measure<3> getPosition() const { return position; }
	bool getCanMove() const { return canMove; }

protected:
	Measure<3> position;
	bool canMove;
};