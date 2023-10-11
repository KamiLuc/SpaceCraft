#pragma once

#include "BasicMesh.h"

class TexturedMesh : public BasicMesh
{
public:
	TexturedMesh();
	virtual ~TexturedMesh();

	void createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices,
					const std::vector<GLfloat>& normals, const std::vector<GLfloat>& textureCoordinates);
	void clearMesh();

protected:
	GLuint textureCoordinatesBuffer;

	void bindBuffers(const std::vector<GLfloat>& textureCoordinates);
};

