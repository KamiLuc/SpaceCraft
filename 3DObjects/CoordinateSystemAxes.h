#pragma once

#include "../../Interfaces/Moveable.h"
#include "../../Interfaces/Renderable.h"

#include <glm/glm.hpp>

class CoordinateSystemAxes : public Renderable, public Moveable
{
public:
	CoordinateSystemAxes(std::shared_ptr<ShaderManager> shaderManager, const glm::vec3& position, float lineWidth = 3.0f, bool immediateRender = false);
	void render(std::shared_ptr<SceneContext> sceneContext) const override;
	glm::mat4 getModelMatrix() const override;
	void setLineWidth(float lineWidth) { this->lineWidth = lineWidth; }
	void setPosition(const glm::vec3& position);
	float* getLineWidthPtr() { return &lineWidth; }

private:
	GLuint VAO;
	GLuint VBO;
	glm::mat4 model;
	glm::vec3 position;
	bool immediateRender;
	float lineWidth;

	void renderWithImmediateMode(std::shared_ptr<SceneContext> sceneContext) const;
};

