#pragma once

#include "../../Interfaces/Moveable.h"
#include "../../Interfaces/Renderable.h"

#include <glm/glm.hpp>

class CoordinateSystemAxes : public Renderable, public Moveable
{
public:
	CoordinateSystemAxes(std::shared_ptr<ShaderManager> shaderManager, const Measure<3>& position);
	void render(std::shared_ptr<SceneContext> sceneContext) const override;
	glm::mat4 getModelMatrix() const override;

private:
	GLuint VAO;
	GLuint VBO;
	glm::mat4 model;
};

