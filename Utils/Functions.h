#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <gl/GL.h>
#include <vector>

#include "../3DRenderer/Mesh.h"

void calculateAverageNormalsLegacy(unsigned int* indices, unsigned int indicesCount, GLfloat* vertices, unsigned int verticesCount, unsigned int vertexLenght, unsigned int normalOffset)
{
	for (size_t i = 0; i < indicesCount; i += 3)
	{
		unsigned int in0 = indices[i] * vertexLenght;
		unsigned int in1 = indices[i + 1] * vertexLenght;
		unsigned int in2 = indices[i + 2] * vertexLenght;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0] += normal.x;
		vertices[in0 + 1] += normal.y;
		vertices[in0 + 2] += normal.z;

		vertices[in1] += normal.x;
		vertices[in1 + 1] += normal.y;
		vertices[in1 + 2] += normal.z;

		vertices[in2] += normal.x;
		vertices[in2 + 1] += normal.y;
		vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticesCount / vertexLenght; i++)
	{
		unsigned int nOffset = static_cast<unsigned int>(i * vertexLenght + normalOffset);
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x;
		vertices[nOffset + 1] = vec.y;
		vertices[nOffset + 2] = vec.z;
	}
}

void calculateAverageNormals(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals)
{
	normals.clear();
	normals.resize(vertices.size(), 0.0f);

	for (size_t i = 0; i < indices.size(); i += 3)
	{
		glm::vec3 v1(vertices[indices[i]], vertices[indices[i] + 1], vertices[indices[i] + 2]);
		glm::vec3 v2(vertices[indices[i + 1]], vertices[indices[i + 1] + 1], vertices[indices[i + 1] + 2]);
		glm::vec3 v3(vertices[indices[i + 2]], vertices[indices[i + 2] + 1], vertices[indices[i + 2] + 2]);
		glm::vec3 faceNormal = glm::normalize(glm::cross(v2 - v1, v3 - v1));

		normals[indices[i]] += faceNormal.x;
		normals[indices[i] + 1] += faceNormal.y;
		normals[indices[i] + 2] += faceNormal.z;
		normals[indices[i + 1]] += faceNormal.x;
		normals[indices[i + 1] + 1] += faceNormal.y;
		normals[indices[i + 1] + 2] += faceNormal.z;
		normals[indices[i + 2]] += faceNormal.x;
		normals[indices[i + 2] + 1] += faceNormal.y;
		normals[indices[i + 2] + 2] += faceNormal.z;
	}

	for (size_t i = 0; i < normals.size(); i += 3)
	{
		glm::vec3 normal(normals[i], normals[i + 1], normals[i + 2]);
		normal = glm::normalize(normal);
		normals[i] = normal.x;
		normals[i + 1] = normal.y;
		normals[i + 2] = normal.z;
	}
}

void createObjects(std::vector<Mesh*>& meshes)
{

	std::vector<GLuint> indices{ 0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2 };
	std::vector<GLfloat> vertices{ -1.0f, -1.0f, -0.6f, 0.0f, -1.0f, 1.0f, 1.0f, -1.0f, -0.6f, 0.0f, 1.0f, 0.0f };
	std::vector<GLfloat> textureCoordinates{ 0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f };
	std::vector<GLfloat> normals{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

	calculateAverageNormals(indices, vertices, normals);


	Mesh* obj1 = new Mesh();
	obj1->createMesh(vertices, indices, textureCoordinates, normals);
	meshes.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->createMesh(vertices, indices, textureCoordinates, normals);
	meshes.push_back(obj2);
}

