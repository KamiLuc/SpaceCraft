#pragma once

#include "../3DRenderer/Mesh/TexturedMesh.h"
#include "../3DRenderer/Texture/Texture.h"

class TexturedSphere : public TexturedMesh
{
public:
	TexturedSphere(const Shader& shader, const Texture& texture, GLuint stacks, GLuint sectors);
	virtual void render(const UniformLocations& uniformLocations) const override;

private:
};
