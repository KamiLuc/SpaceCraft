#include "Mesh.h"

Mesh::Mesh() : VAO(0), vertexBuffer(0), indicesBuffer(0), textureCoordinatesBuffer(0), normalsBuffer(0), indexCount(0)
{
}

Mesh::~Mesh()
{
	this->clearMesh();
}

void Mesh::createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& textureCoordinates, const std::vector<GLfloat>& normals)
{
	indexCount = static_cast<GLsizei>(indices.size());

	//remember to unbind
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);

	if (!textureCoordinates.empty()) {
		glGenBuffers(1, &textureCoordinatesBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, textureCoordinatesBuffer);
		glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(GLfloat), textureCoordinates.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(1);
	}

	if (!normals.empty()) {
		glGenBuffers(1, &normalsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(2);
	}

	//unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::renderMesh()
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	// When not using index drawing glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void Mesh::clearMesh()
{
	if (indicesBuffer != 0)
	{
		//delete buffer from graphic card memory
		glDeleteBuffers(1, &indicesBuffer);
		indicesBuffer = 0;
	}

	if (vertexBuffer != 0)
	{
		//delete buffer from graphic card memory
		glDeleteBuffers(1, &vertexBuffer);
		vertexBuffer = 0;
	}

	if (normalsBuffer != 0)
	{
		//delete buffer from graphic card memory
		glDeleteBuffers(1, &normalsBuffer);
		normalsBuffer = 0;
	}

	if (textureCoordinatesBuffer != 0)
	{
		//delete buffer from graphic card memory
		glDeleteBuffers(1, &textureCoordinatesBuffer);
		textureCoordinatesBuffer = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}
