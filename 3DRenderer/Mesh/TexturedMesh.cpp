#include "TexturedMesh.h"

TexturedMesh::TexturedMesh(std::shared_ptr<Shader> shader) : BasicMesh(shader), textureCoordinatesBuffer(0)
{
}

TexturedMesh::~TexturedMesh()
{
	clearMesh();
}

void TexturedMesh::createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& normals, const std::vector<GLfloat>& textureCoordinates)
{
	beginMeshCreation();
	BasicMesh::bindBuffers(vertices, indices, normals);
	bindBuffers(textureCoordinates);
	endMeshCreation();
}

void TexturedMesh::clearMesh()
{
	if (textureCoordinatesBuffer != 0)
	{
		glDeleteBuffers(1, &textureCoordinatesBuffer);
		textureCoordinatesBuffer = 0;
	}

	BasicMesh::clearMesh();
}

void TexturedMesh::render()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void TexturedMesh::bindBuffers(const std::vector<GLfloat>& textureCoordinates)
{
	if (!textureCoordinates.empty()) {
		glGenBuffers(1, &textureCoordinatesBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, textureCoordinatesBuffer);
		glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(GLfloat), textureCoordinates.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(1);
	}
}
