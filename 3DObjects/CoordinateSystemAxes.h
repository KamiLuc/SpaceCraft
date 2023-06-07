#pragma once

#include "../../Interfaces/Moveable.h"
#include "../../Interfaces/Renderable.h"

#include <glm/glm.hpp>

class CoordinateSystemAxes : public Renderable, public Moveable
{
public:
	CoordinateSystemAxes(const Shader& shader, const Measure<3>& position);
	void render(const UniformLocations& uniformLocations) const override;

private:
	GLuint VAO;
	GLuint VBO;
	glm::mat4 model;
};

