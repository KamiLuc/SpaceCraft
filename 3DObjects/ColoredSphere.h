#pragma once

#include "../3DRenderer/Mesh/ColoredMesh.h"

class ColoredSphere : public ColoredMesh
{
public:
	ColoredSphere(const Shader& shader, const glm::vec4& color, GLuint stacks, GLuint sectors);
	ColoredSphere(const Shader& shader, const std::vector<GLfloat>& colors, GLuint stacks, GLuint sectors);
	virtual void render(const UniformLocations& uniformLocations) const override;

private:
	void createSphere(GLuint stacks, GLuint sectors, GLfloat radius, const std::vector<GLfloat>& colors);
};
