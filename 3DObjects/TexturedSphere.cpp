#include "TexturedSphere.h"

#include <vector>
#include <glm/gtc/type_ptr.hpp>

TexturedSphere::TexturedSphere(const Shader& shader, const::glm::vec3& position,
	GLuint stacks, GLuint sectors)
	: TexturedMesh(shader), Moveable(position)
{
	std::vector<GLfloat> vertices{};
	std::vector<GLfloat> textureCoordinates{};
	std::vector<GLfloat> normals{};
	std::vector<GLuint> indices{};

	const float PI = static_cast<float>(acos(-1.0f));
	const float radius = 1.0f;

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

			textureCoordinates.emplace_back(static_cast<GLfloat>(j) / sectors);
			textureCoordinates.emplace_back(static_cast<GLfloat>(i) / stacks);

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

	createMesh(vertices, indices, normals, textureCoordinates);
}

void TexturedSphere::render(const UniformLocations& uniformLocations)
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, position);
	glUniformMatrix4fv(uniformLocations.uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}
