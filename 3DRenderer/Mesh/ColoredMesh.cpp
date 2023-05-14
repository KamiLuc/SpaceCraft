#include "ColoredMesh.h"

ColoredMesh::ColoredMesh(const Shader& shader) : BasicMesh(shader), verticesColorBuffer(0)
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

	BasicMesh::clearMesh();
}

void ColoredMesh::render(const UniformLocations& uniformLocations)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
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
