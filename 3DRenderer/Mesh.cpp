#include "Mesh.h"

Mesh::Mesh() : VAO(0), VBO(0), IBO(0), indexCount(0)
{
}

Mesh::~Mesh()
{
	this->clearMesh();
}

void Mesh::createMesh(GLfloat* vertices, uint32_t* indices, uint32_t numberOfVertices, uint32_t numberOfIndices)
{
	indexCount = numberOfIndices;

	//remember to unbind
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numberOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numberOfVertices, vertices, GL_STATIC_DRAW);

	//3 - xyz
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, nullptr);

	//0 == upper 1
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	//unbind
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::renderMesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	// When not using index drawing glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::clearMesh()
{
	if (IBO != 0)
	{
		//delete buffer from graphic card memory
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		//delete buffer from graphic card memory
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}
