#pragma once

#include <GL\glew.h>

class Material
{
public:
	Material();
	Material(GLfloat intensity, GLfloat shine);
	~Material();

	void useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation) const;
	GLfloat* getSpecularIntensityPtr() { return &specularIntensity; }
	GLfloat* getShininessPtr() { return &shininess; }

private:
	GLfloat specularIntensity;
	GLfloat shininess;
};

