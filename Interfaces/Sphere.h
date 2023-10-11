#pragma once

#include "Utils/Functions.h"
#include "3DRenderer/Mesh/BasicMesh.h"
#include "Utils/PhysicalUnit.h"

#include <vector>
#include <GL/glew.h>
#include <GL/GL.h>

class Sphere
{
public:
	Sphere() : Sphere(0, 0, 0) {}
	Sphere(const PhysicalUnit& radius, unsigned int stacks, unsigned int sectors);
	~Sphere() {}

	PhysicalUnit getRadius() const;
	void setRadius(const PhysicalUnit& radius);
	void createSphere(std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals, std::vector<unsigned int>& indices);

protected:
	PhysicalUnit radius;
	unsigned int stacks;
	unsigned int sectors;
};

