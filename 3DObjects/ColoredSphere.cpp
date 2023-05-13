#include "ColoredSphere.h"

#include <ctime>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ColoredSphere::ColoredSphere(std::shared_ptr<Shader> shader, const::glm::vec3& position,
	GLuint stacks, GLuint sectors, glm::vec4 color)
	: ColoredMesh(shader), Moveable(position)
{
	std::vector<GLfloat> colors((stacks + 1) * (sectors + 1) * 4);
	GLfloat radius = 1.0f;
	for (size_t i = 0; i < colors.size() / 4; i += 1) {
		colors[i * 4] = color[0];
		colors[i * 4 + 1] = color[1];
		colors[i * 4 + 2] = color[2];
		colors[i * 4 + 3] = color[3];
	}

	createSphere(stacks, sectors, radius, colors);
}

ColoredSphere::ColoredSphere(std::shared_ptr<Shader> shader, const::glm::vec3& position,
	GLuint stacks, GLuint sectors, const std::vector<GLfloat>& colors)
	: ColoredMesh(shader), Moveable(position)
{
	GLfloat radius = 1.0f;
	createSphere(stacks, sectors, radius, colors);
}

void ColoredSphere::render(const UniformLocations& uniformLocations)
{
	glm::mat4 model(1.0f);
	glUniformMatrix4fv(uniformLocations.uniformModel, 1, GL_FALSE, glm::value_ptr(glm::translate(model, position)));
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 6);
	glBindVertexArray(0);
}

void ColoredSphere::createSphere(GLuint stacks, GLuint sectors, GLfloat radius, const std::vector<GLfloat>& colors)
{
	std::vector<GLfloat> vertices{};
	std::vector<GLfloat> normals{};
	std::vector<GLuint> indices{};
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	const float PI = static_cast<float>(acos(-1.0f));

	GLfloat sectorStep = 2 * PI / sectors;
	GLfloat stackStep = PI / stacks;
	GLfloat sectorAngle, stackAngle;
	GLfloat lengthInv = 1.0f / radius;

	for (GLuint i = 0; i <= stacks; ++i) {
		stackAngle = PI / 2 - i * stackStep;
		auto xy = radius * cosf(stackAngle);

		for (GLuint j = 0; j <= sectors; ++j) {
			sectorAngle = j * sectorStep;

			auto x = xy * cosf(sectorAngle);
			auto y = xy * sinf(sectorAngle);

			auto z = radius * sinf(stackAngle);
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			normals.emplace_back(x * lengthInv);
			normals.emplace_back(y * lengthInv);
			normals.emplace_back(z * lengthInv);
		}
	}

	for (GLuint i = 0; i < stacks; ++i) {
		GLuint k1 = i * (sectors + 1);
		GLuint k2 = k1 + sectors + 1;

		for (GLuint j = 0; j < sectors; ++j, ++k1, ++k2) {
			if (i != 0) {
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k1);
			}

			if (i != stacks - 1) {
				indices.push_back(k2 + 1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}
		}
	}

	BasicMesh::calculateAverageNormals(indices, vertices, normals);

	createMesh(vertices, indices, normals, colors);
}