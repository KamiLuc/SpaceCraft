#pragma once

#include "Utils/CircularVector.h"
#include "Interfaces/Renderable.h"

class Orbit : public CircularVector<glm::vec3>, Renderable
{
public:
	Orbit() : Orbit(0, { 0.0f,0.0f,0.0f }) {}
	Orbit(size_t maxSize, const glm::vec3 orbitColor);
	virtual ~Orbit();

	glm::vec3 getColor() const { return color; }
	void setColor(const glm::vec3& color) { this->color = color; }
	void addPoint(const glm::vec3& point);
	virtual void render(SceneContext& sceneContext) const override;

private:
	glm::vec3 color;
	GLuint VBO;
	GLuint VAO;
};

