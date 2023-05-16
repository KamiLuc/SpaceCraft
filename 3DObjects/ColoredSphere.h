#pragma once

#include "../3DRenderer/Mesh/ColoredMesh.h"
#include "../../3DObjects/Interfaces/Moveable.h"

class ColoredSphere : public ColoredMesh, public Moveable
{
public:
	ColoredSphere(const Shader& shader, const glm::vec<3, Measure>& position, GLuint stacks, GLuint sectors, const glm::vec4& color);
	ColoredSphere(const Shader& shader, const glm::vec<3, Measure>& position, GLuint stacks, GLuint sectors, const std::vector<GLfloat>& colors);
	virtual void render(const UniformLocations& uniformLocations) override;

private:
	void createSphere(GLuint stacks, GLuint sectors, GLfloat radius, const std::vector<GLfloat>& colors);
};
