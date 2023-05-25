#pragma once

#include <glm/glm.hpp>

class Colored {
public:
	Colored(const glm::vec4& color) : color(color) {}

	void setColor(const glm::vec4& color) {
		this->color = color;
	}

	glm::vec4 getColor() const {
		return this->color;
	}

protected:
	glm::vec4 color;
};