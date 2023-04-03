#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <gl/GL.h>
#include <vector>

#include "../3DRenderer/Mesh.h"


void calculateAverageNormals(unsigned int* indices, unsigned int indicesCount, GLfloat* vertices, unsigned int verticesCount, unsigned int vertexLenght, unsigned int normalOffset)
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
		unsigned int nOffset = i * vertexLenght + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x;
		vertices[nOffset + 1] = vec.y;
		vertices[nOffset + 2] = vec.z;
	}
}

void generateSphere(float radius, int sectorCount, int stackCount, std::vector<GLfloat>& vertices, std::vector<unsigned int>& indices) {

	auto PI = 3.14159265f;

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i) {
		stackAngle = PI / 2 - i * stackStep;
		float xy = radius * cos(stackAngle);
		float z = radius * sin(stackAngle);

		for (int j = 0; j <= sectorCount; ++j) {
			sectorAngle = j * sectorStep;
			float x = xy * cos(sectorAngle);
			float y = xy * sin(sectorAngle);

			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);
			vertices.push_back(float(j) / sectorCount);
			vertices.push_back(float(i) / stackCount);

		}
	}

	for (int i = 0; i < stackCount; ++i) {
		int k1 = i * (sectorCount + 1);
		int k2 = k1 + sectorCount + 1;

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
			if (i != 0) {
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			if (i != (stackCount - 1)) {
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}
}


void createShaders(std::vector<Shader*>& shaders, const std::filesystem::path fShader, const std::filesystem::path vShader) {
	Shader* shader1 = new Shader();
	shader1->createFromFiles(vShader, fShader);
	shaders.push_back(shader1);
}

void createObjects(std::vector<Mesh*>& meshes)
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1 ,2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};


	calculateAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh();
	obj1->createMesh(vertices, indices, 32, 12);
	meshes.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->createMesh(vertices, indices, 32, 12);
	meshes.push_back(obj2);
}

