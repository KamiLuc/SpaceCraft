#pragma once

#include "../3DRenderer/Interfaces/Renderable.h"
#include "../3DRenderer/Interfaces/Moveable.h"

#include <glm/glm.hpp>

class CoordinateSystemAxes : public Renderable, public Moveable
{
public:
	CoordinateSystemAxes(std::shared_ptr<Shader> shader, const glm::vec3& position);
	void render(const UniformLocations& uniformLocations) override;

private:
	GLuint VAO;
	GLuint VBO;
	glm::mat4 model;
};

