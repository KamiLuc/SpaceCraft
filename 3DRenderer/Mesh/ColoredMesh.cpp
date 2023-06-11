#include "ColoredMesh.h"

ColoredMesh::ColoredMesh()
	: verticesColorBuffer(0)
{
}

ColoredMesh::~ColoredMesh()
{
	clearMesh();
}

void ColoredMesh::createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices,
	const std::vector<GLfloat>& normals, const std::vector<GLfloat>& verticesColorBuffer)
{
	beginMeshCreation();
	BasicMesh::bindBuffers(vertices, indices, normals);
	bindBuffers(verticesColorBuffer);
	endMeshCreation();
}

void ColoredMesh::clearMesh()
{
	if (verticesColorBuffer != 0)
	{
		glDeleteBuffers(1, &verticesColorBuffer);
		verticesColorBuffer = 0;
	}
}

void ColoredMesh::bindSingleColor(const glm::vec<4, GLfloat>& color)
{
	GLint bufferSize = 0;
	glBindBuffer(GL_ARRAY_BUFFER, verticesColorBuffer);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);

	GLsizei dataSize = bufferSize / sizeof(GLfloat);
	std::vector<GLfloat> data(dataSize);

	for (GLsizei i = 0; i < dataSize / 4; i++) {
		data[4 * i] = color[0];
		data[4 * i + 1] = color[1];
		data[4 * i + 2] = color[2];
		data[4 * i + 3] = color[3];
	}

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ColoredMesh::bindBuffers(const std::vector<GLfloat>& verticesColors)
{
	if (!verticesColors.empty()) {
		glGenBuffers(1, &verticesColorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, verticesColorBuffer);
		glBufferData(GL_ARRAY_BUFFER, verticesColors.size() * sizeof(GLfloat), verticesColors.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(3);
	}
}
