#pragma once

#include <GL/glew.h>
#include <glm/ext/vector_float3.hpp>

#include "../../Utils/Measure.h"

class Moveable {
public:
	Moveable(const Measure<3>& position) : position(position) {};
	virtual ~Moveable() {}
	void moveBy(const Measure<3>& position) { this->position += position; }
	void setPosition(const Measure<3>& position) { this->position = position; }
	void setPosition(const glm::vec3 position, int exponent) {
		this->position = Measure<3>(position, exponent);
	}

protected:
	Measure<3> position;
};