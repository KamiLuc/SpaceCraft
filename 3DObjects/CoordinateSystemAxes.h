#pragma once

#include "Interfaces/Moveable.h"
#include "Interfaces/Renderable.h"

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CoordinateSystemAxes : public Renderable, public Moveable
{
public:
	CoordinateSystemAxes(const glm::vec3& position, float lineWidth = 3.0f, bool immediateRender = false);
	~CoordinateSystemAxes();

	glm::mat4 getModelMatrix() const;
	void render(SceneContext& sceneContext) const override;
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

	void renderWithImmediateMode(SceneContext& sceneContext) const;
};

