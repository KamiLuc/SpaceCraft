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

protected:
	glm::vec<3, Measure> position;
};