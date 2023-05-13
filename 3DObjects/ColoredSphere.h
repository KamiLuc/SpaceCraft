#pragma once

#include "../3DRenderer/Mesh/ColoredMesh.h"
#include "../3DRenderer/Interfaces/Moveable.h"

class ColoredSphere : public ColoredMesh, public Moveable
{
public:
	ColoredSphere(std::shared_ptr<Shader> shader, const::glm::vec3& position, GLuint stacks, GLuint sectors, glm::vec4 color);
	ColoredSphere(std::shared_ptr<Shader> shader, const::glm::vec3& position, GLuint stacks, GLuint sectors, const std::vector<GLfloat>& colors);
	virtual void render(const UniformLocations& uniformLocations) override;

private:
	void createSphere(GLuint stacks, GLuint sectors, GLfloat radius, const std::vector<GLfloat>& colors);
};
