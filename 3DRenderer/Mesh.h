#pragma once

#include <GL\glew.h>
#include <cstdint>

#include <vector>
#include <glm/glm.hpp>

class Mesh
{
public:
	Mesh();
	~Mesh();
	void createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& textureCoordinates, const std::vector<GLfloat>& normals);
	void renderMesh();
	void clearMesh();

private:
	GLuint VAO;
	GLuint vertexBuffer;
	GLuint indicesBuffer;
	GLuint normalsBuffer;
	GLuint textureCoordinatesBuffer;
	GLsizei indexCount;
};

