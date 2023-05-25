#include "ColoredSphere.h"
#include "../3DRenderer/Shader/Shader.h"

#include <ctime>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


ColoredSphere::ColoredSphere(const Shader& shader, const glm::vec4& color, GLuint stacks, GLuint sectors)
	: ColoredMesh(shader)
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

ColoredSphere::ColoredSphere(const Shader& shader, const std::vector<GLfloat>& colors, GLuint stacks, GLuint sectors)
	: ColoredMesh(shader)
{
	GLfloat radius = 1.0f;
	createSphere(stacks, sectors, radius, colors);
}

void ColoredSphere::render(const UniformLocations& uniformLocations) const
{
	ColoredMesh::render(uniformLocations);
}
void ColoredSphere::createSphere(GLuint stacks, GLuint sectors, GLfloat radius, const std::vector<GLfloat>& colors)
{
	std::vector<GLfloat> vertices{};
	std::vector<GLfloat> normals{};
	std::vector<GLuint> indices{};

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

			/*
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
			*/

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
