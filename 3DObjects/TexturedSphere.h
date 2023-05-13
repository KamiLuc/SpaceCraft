#pragma once

#include "../3DRenderer/Mesh/TexturedMesh.h"

class TexturedSphere : public TexturedMesh
{
public:
	TexturedSphere(std::shared_ptr<Shader> shader, GLuint stacks, GLuint sectors);

private:
};
