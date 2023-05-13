#pragma once

#include <GL\glew.h>
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>

#include "../Interfaces/Renderable.h"

class BasicMesh : public Renderable
{
public:
	BasicMesh(std::shared_ptr<Shader> shader);
	virtual ~BasicMesh();

	void createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices,
		const std::vector<GLfloat>& normals);
	void clearMesh();

	virtual void render() override;

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

