#include "BasicMesh.h"

BasicMesh::BasicMesh(const Shader& shader) : VAO(0), vertexBuffer(0), indicesBuffer(0), normalsBuffer(0), indexCount(0), Renderable(shader)
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

void BasicMesh::endMeshCreation()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BasicMesh::render(const UniformLocations& uniformLocations)
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void BasicMesh::calculateAverageNormals(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals)
{
	normals.clear();
	normals.resize(vertices.size(), 0.0f);

	for (size_t i = 0; i < indices.size(); i += 3) {

		glm::vec3 v1(vertices[3 * indices[i]], vertices[3 * indices[i] + 1], vertices[3 * indices[i] + 2]);
		glm::vec3 v2(vertices[3 * indices[i + 1]], vertices[3 * indices[i + 1] + 1], vertices[3 * indices[i + 1] + 2]);
		glm::vec3 v3(vertices[3 * indices[i + 2]], vertices[3 * indices[i + 2] + 1], vertices[3 * indices[i + 2] + 2]);
		glm::vec3 faceNormal = glm::normalize(glm::cross(v2 - v1, v3 - v1));

		normals[3 * indices[i]] += faceNormal.x;
		normals[3 * indices[i] + 1] += faceNormal.y;
		normals[3 * indices[i] + 2] += faceNormal.z;
		normals[3 * indices[i + 1]] += faceNormal.x;
		normals[3 * indices[i + 1] + 1] += faceNormal.y;
		normals[3 * indices[i + 1] + 2] += faceNormal.z;
		normals[3 * indices[i + 2]] += faceNormal.x;
		normals[3 * indices[i + 2] + 1] += faceNormal.y;
		normals[3 * indices[i + 2] + 2] += faceNormal.z;
	}

	for (size_t i = 0; i < normals.size(); i += 3) {

		glm::vec3 normal(normals[i], normals[i + 1], normals[i + 2]);
		normal = glm::normalize(normal);
		normals[i] = normal.x;
		normals[i + 1] = normal.y;
		normals[i + 2] = normal.z;
	}
}
