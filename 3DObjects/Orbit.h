#pragma once

#include "Utils/CircularVector.h"
#include "Interfaces/Renderable.h"

class Orbit : public CircularVector<glm::vec3>, public Renderable
{
public:
	Orbit();
	Orbit(size_t maxSize, const glm::vec3 orbitColor);
	virtual ~Orbit();

	virtual void render(SceneContext& sceneContext) const override;
	void addPoint(const glm::vec3& point);

	glm::vec3 getColor() const;
	void setColor(const glm::vec3& color);

private:
	glm::vec3 color;
	GLuint VBO;
	GLuint VAO;
};

