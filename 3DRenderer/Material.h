#pragma once

#include <GL\glew.h>

class Material
{
public:
	Material();
	Material(GLfloat intensity, GLfloat shine);
	~Material();

	void useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);

private:
	GLfloat specularIntensity;
	GLfloat shininess;
};

