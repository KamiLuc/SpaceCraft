#pragma once

#include <GL/glew.h>

#include <glm/ext/vector_float3.hpp>

class Moveable {
public:
	Moveable(const glm::vec3& position) : position(position) {};
	virtual ~Moveable() {}
	void moveBy(const glm::vec3& position) { this->position += position; }
	void moveTo(const glm::vec3& position) { this->position = position; }

protected:
	glm::vec3 position;
};