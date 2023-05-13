#pragma once

#include "../3DRenderer/Interfaces/Renderable.h"

#include <glm/glm.hpp>

class CoordinateSystemAxes : public Renderable
{
public:
	CoordinateSystemAxes(std::shared_ptr<Shader> shader);
	void render() override;

private:
	GLuint VAO;
	GLuint VBO;
};

