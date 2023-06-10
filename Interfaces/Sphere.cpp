#include "Sphere.h"

Sphere::Sphere(const Measure<1> radius, unsigned int stacks, unsigned int sectors)
	: radius(radius)
	, stacks(stacks)
	, sectors(sectors)
{
}

Measure<1> Sphere::getRadius() const
{
	return radius;
}

void Sphere::setRadius(const Measure<1> radius)
{
	this->radius = radius;
}

void Sphere::createSphere(std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals, std::vector<unsigned int>& indices)
{
	const float PI = static_cast<float>(acos(-1.0f));

	GLfloat radius = 1.0f;
	GLfloat sectorStep = 2 * PI / sectors;
	GLfloat stackStep = PI / stacks;
	GLfloat sectorAngle, stackAngle;
	GLfloat lengthInv = 1.0f / radius;

	for (unsigned int i = 0; i <= stacks; ++i) {
		stackAngle = PI / 2 - i * stackStep;
		auto xy = radius * cosf(stackAngle);

		for (unsigned int j = 0; j <= sectors; ++j) {
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

	for (unsigned int i = 0; i < stacks; ++i) {
		unsigned int k1 = i * (sectors + 1);
		unsigned int k2 = k1 + sectors + 1;

		for (unsigned int j = 0; j < sectors; ++j, ++k1, ++k2) {

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

	calculateAverageNormals(indices, vertices, normals);
}
