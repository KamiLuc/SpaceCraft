#pragma once

#include "../../3DObjects/Interfaces/Moveable.h"
#include "../../3DObjects/Interfaces/Renderable.h"

#include <glm/glm.hpp>

class CoordinateSystemAxes : public Renderable, public Moveable
{
public:
	CoordinateSystemAxes(const Shader& shader, const glm::vec<3, Measure>& position);
	void render(const UniformLocations& uniformLocations) override;

private:
	GLuint VAO;
	GLuint VBO;
	glm::mat4 model;
};

