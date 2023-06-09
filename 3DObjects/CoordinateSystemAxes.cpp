#include "CoordinateSystemAxes.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

CoordinateSystemAxes::CoordinateSystemAxes(const Shader& shader, const Measure<3>& position)
	: VAO(-1), VBO(-1), Renderable(shader), Moveable(position), model(1.0f)
{
	model = glm::translate(model, position.getGlmVec());

	GLfloat axisVertices[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
}

void CoordinateSystemAxes::render(const UniformLocations& uniformLocations) const
{
	glUniformMatrix4fv(uniformLocations.uniformModel, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 6);
	glBindVertexArray(0);
}

glm::mat4 CoordinateSystemAxes::getModelMatrix() const
{
	GLfloat m = 100000.0f;
	return glm::scale(model, glm::vec3(m, m, m));
}
