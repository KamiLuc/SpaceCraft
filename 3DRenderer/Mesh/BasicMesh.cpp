#include "BasicMesh.h"

BasicMesh::BasicMesh()
	: VAO(0)
	, vertexBuffer(0)
	, indicesBuffer(0)
	, normalsBuffer(0)
	, indexCount(0)
{
}

BasicMesh::~BasicMesh()
{
	clearMesh();
}

void BasicMesh::beginMeshCreation()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void BasicMesh::bindBuffers(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& normals)
{
	indexCount = static_cast<GLsizei>(indices.size());

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &indicesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);

	if (!normals.empty()) {
		glGenBuffers(1, &normalsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(2);
	}
}

void BasicMesh::createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& normals)
{
	beginMeshCreation();
	bindBuffers(vertices, indices, normals);
	endMeshCreation();
}

void BasicMesh::clearMesh()
{
	if (indicesBuffer != 0)
	{
		glDeleteBuffers(1, &indicesBuffer);
		indicesBuffer = 0;
	}

	if (vertexBuffer != 0)
	{
		glDeleteBuffers(1, &vertexBuffer);
		vertexBuffer = 0;
	}

	if (normalsBuffer != 0)
	{
		glDeleteBuffers(1, &normalsBuffer);
		normalsBuffer = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
}

void BasicMesh::useMesh() const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void BasicMesh::endMeshCreation()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
