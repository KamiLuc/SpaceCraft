#pragma once

#include "BasicMesh.h"
#include "../../3DObjects/Interfaces/Textured.h"

class TexturedMesh : public BasicMesh, public Textured
{
public:
	TexturedMesh(const Shader& shader, const Texture& texture);
	virtual ~TexturedMesh();

	void createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices,
		const std::vector<GLfloat>& normals, const std::vector<GLfloat>& textureCoordinates);
	void clearMesh();

	virtual void render(const UniformLocations& uniformLocations) override;

protected:
	void bindBuffers(const std::vector<GLfloat>& textureCoordinates);
	GLuint textureCoordinatesBuffer;
};

