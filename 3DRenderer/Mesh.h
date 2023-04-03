#pragma once

#include <GL\glew.h>
#include <cstdint>

class Mesh
{
public:
	Mesh();
	~Mesh();
	void createMesh(GLfloat* vertices, uint32_t* indices, uint32_t numberOfVertices, uint32_t numberOfIndices);
	void renderMesh();
	void clearMesh();

private:
	GLuint VAO;
	GLuint VBO;
	GLuint IBO;
	GLsizei indexCount;
};

