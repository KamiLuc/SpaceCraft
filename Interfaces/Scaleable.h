#pragma once

#include <glm/detail/qualifier.hpp>

class Scaleable {
public:
	Scaleable() : scale(0.0f) {}
	Scaleable(float scale) : scale(scale) {};
	virtual ~Scaleable() {}

	void setScale(float scale) { this->scale = scale; }
	float getScale() const { return scale; }

protected:
	float scale;
};