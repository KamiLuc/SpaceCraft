#pragma once

#include <GL\glew.h>
#include <cstdint>

#include <vector>
#include <glm/glm.hpp>


class BasicMesh
{
public:
	BasicMesh();
	virtual ~BasicMesh();

	void createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices,
		const std::vector<GLfloat>& normals);
	void clearMesh();

	virtual void renderMesh() = 0;

	static void calculateAverageNormals(const std::vector<unsigned int>& indices, const std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals);

protected:
	void beginMeshCreation();
	void bindBuffers(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices, const std::vector<GLfloat>& normals);
	void endMeshCreation();

	GLuint VAO;
	GLuint vertexBuffer;
	GLuint indicesBuffer;
	GLuint normalsBuffer;
	GLsizei indexCount;
};

