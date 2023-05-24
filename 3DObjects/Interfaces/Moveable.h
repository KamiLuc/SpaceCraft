#pragma once

#include <GL/glew.h>
#include <glm/ext/vector_float3.hpp>

#include "../../Utils/Measure.h"

class Moveable {
public:
	Moveable(const glm::vec<3, Measure>& position) : position(position) {};
	virtual ~Moveable() {}
	void moveBy(const glm::vec<3, Measure>& position) { this->position += position; }
	void setPosition(const glm::vec<3, Measure>& position) { this->position = position; }
	void setPosition(const glm::vec3 position, int exponent) {
		this->position = glm::vec<3, Measure>({ position.x, exponent }, { position.y, exponent }, { position.z, exponent });
	}

protected:
	glm::vec<3, Measure> position;
};