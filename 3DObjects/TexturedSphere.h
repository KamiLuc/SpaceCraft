#pragma once

#include "../3DRenderer/Mesh/TexturedMesh.h"
#include "../3DRenderer/Interfaces/Moveable.h"

class TexturedSphere : public TexturedMesh, public Moveable
{
public:
	TexturedSphere(const Shader& shader, const::glm::vec3& position, GLuint stacks, GLuint sectors);
	virtual void render(const UniformLocations& uniformLocations) override;

private:
};
