#include "Sphere.h"

#include <vector>

Sphere::Sphere(GLuint stacks, GLuint sectors, GLfloat radius)
{
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

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

			vertices.emplace_back(static_cast<GLfloat>(j) / sectors);
			vertices.emplace_back(static_cast<GLfloat>(i) / stacks);

			vertices.emplace_back(x * lengthInv);
			vertices.emplace_back(y * lengthInv);
			vertices.emplace_back(z * lengthInv);
		}
	}

	for (GLuint i = 0; i < stacks; ++i) {
		GLuint k1 = i * (sectors + 1);
		GLuint k2 = k1 + sectors + 1;

		for (GLuint j = 0; j < sectors; ++j, ++k1, ++k2) {
			if (i != 0) {
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			if (i != stacks - 1) {
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

	this->createMesh(vertices.data(), indices.data(),
		static_cast<uint32_t>(vertices.size()), static_cast<uint32_t>(indices.size()));
}