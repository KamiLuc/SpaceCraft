#pragma once

#include "../3DRenderer/Mesh/ColoredMesh.h"

class ColoredSphere : public ColoredMesh
{
public:
	ColoredSphere(std::shared_ptr<Shader> shader, GLuint stacks, GLuint sectors, glm::vec4 color);
	ColoredSphere(std::shared_ptr<Shader> shader, GLuint stacks, GLuint sectors, const std::vector<GLfloat>& colors);

private:
	void createSphere(GLuint stacks, GLuint sectors, GLfloat radius, const std::vector<GLfloat>& colors);
};
