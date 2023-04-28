#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <gl/GL.h>
#include <vector>

#include "../3DRenderer/Mesh/TexturedMesh.h"
#include "../3DRenderer/Mesh/ColoredMesh.h"

void createObjects(std::vector<BasicMesh*>& meshes)
{
	std::vector<GLuint> indices{ 0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2 };
	std::vector<GLfloat> vertices{ -1.0f, -1.0f, -0.6f, 0.0f, -1.0f, 1.0f, 1.0f, -1.0f, -0.6f, 0.0f, 1.0f, 0.0f };
	std::vector<GLfloat> textureCoordinates{ 0.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f };
	std::vector<GLfloat> verticesColors{ 0.1f, 0.5f, 0.8f, 0.5f, 0.2f, 0.5f, 0.9f, 0.3f, 0.6f, 0.8f, 0.8f, 0.5f, 0.8f, 0.2f, 0.2f, 0.5f };
	std::vector<GLfloat> normals{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

	BasicMesh::calculateAverageNormals(indices, vertices, normals);

	TexturedMesh* obj1 = new TexturedMesh();
	obj1->createMesh(vertices, indices, normals, textureCoordinates);
	meshes.push_back(obj1);

	ColoredMesh* obj2 = new ColoredMesh();
	obj2->createMesh(vertices, indices, normals, verticesColors);
	meshes.push_back(obj2);
}

