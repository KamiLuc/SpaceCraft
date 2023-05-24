#pragma once

#include <GL\glew.h>
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>

#include "../../3DObjects/Interfaces/Renderable.h"
#include "../Shader/Shader.h"

class BasicMesh : public Renderable
{
public:
	BasicMesh(const Shader& shader);
	virtual ~BasicMesh();

	virtual void createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices,
		const std::vector<GLfloat>& normals);
	virtual void clearMesh();

	virtual void render(const UniformLocations& uniformLocations) const override;

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

