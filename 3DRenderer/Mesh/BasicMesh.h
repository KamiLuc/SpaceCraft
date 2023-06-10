#pragma once

#include <GL\glew.h>
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>

class BasicMesh {
public:
	BasicMesh();
	virtual ~BasicMesh();

	virtual void createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices,
		const std::vector<GLfloat>& normals);
	virtual void clearMesh();
	virtual void useMesh() const;

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

