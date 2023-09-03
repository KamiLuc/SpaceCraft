#pragma once

#include "../Utils/CircularVector.h"
#include "../Interfaces/Renderable.h"

class Orbit : public CircularVector<glm::vec3>, Renderable
{
public:
	Orbit(size_t maxSize, const glm::vec3 orbitColor, std::shared_ptr<ShaderManager> shaderManager);
	virtual ~Orbit();

	glm::vec3 getColor() const { return color; }
	void setColor(const glm::vec3& color) { this->color = color; }
	void addPoint(const glm::vec3& point);
	virtual void render(std::shared_ptr<SceneContext> sceneContext) const override;

private:
	glm::vec3 color;
	GLuint VBO;
	GLuint VAO;
};

