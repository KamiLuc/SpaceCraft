#pragma once

#include "BasicMesh.h"

class TexturedMesh : public BasicMesh
{
public:
	TexturedMesh(std::shared_ptr<Shader> shader);
	virtual ~TexturedMesh();

	void createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices,
		const std::vector<GLfloat>& normals, const std::vector<GLfloat>& textureCoordinates);
	void clearMesh();

	virtual void render() override;

private:
	void bindBuffers(const std::vector<GLfloat>& textureCoordinates);

	GLuint textureCoordinatesBuffer;
};

