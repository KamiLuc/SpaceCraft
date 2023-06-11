#pragma once

#include "../Utils/Measure.h"
#include "../Utils/Functions.h"
#include "../3DRenderer/Mesh/BasicMesh.h"

#include <vector>
#include <GL/glew.h>
#include <GL/GL.h>

class Sphere
{
public:
	Sphere(const Measure<1> radius, unsigned int stacks, unsigned int sectors);
	~Sphere() {}

	Measure<1> getRadius() const;
	void setRadius(const Measure<1> radius);
	void createSphere(std::vector<GLfloat>& vertices, std::vector<GLfloat>& normals, std::vector<unsigned int>& indices);

protected:
	Measure<1> radius;
	unsigned int stacks;
	unsigned int sectors;
};

