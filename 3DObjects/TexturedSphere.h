#pragma once

#include "../3DRenderer/Mesh/TexturedMesh.h"
#include "../../3DObjects/Interfaces/Moveable.h"
#include "../3DRenderer/Texture/Texture.h"

class TexturedSphere : public TexturedMesh, public Moveable
{
public:
	TexturedSphere(const Shader& shader, const Texture& texture, const glm::vec<3, Measure>& position, GLuint stacks, GLuint sectors);
	virtual void render(const UniformLocations& uniformLocations) override;

private:
};
