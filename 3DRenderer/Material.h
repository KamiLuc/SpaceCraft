#pragma once

#include "AppFramework/Serializer/Serializable.h"

#include <GL\glew.h>

class Material
{
public:
	Material();
	Material(GLfloat intensity, GLfloat shine);
	~Material();

	GLfloat getSpecularIntensity() const { return specularIntensity; }
	GLfloat* getSpecularIntensityPtr() { return &specularIntensity; }
	void setSpecularIntensity(GLfloat specularIntensity) { this->specularIntensity = specularIntensity; }
	GLfloat getShininess() const { return shininess; }
	GLfloat* getShininessPtr() { return &shininess; }
	void setSpecularShininess(GLfloat setSpecularShininess) { this->specularIntensity = specularIntensity; }

private:
	GLfloat specularIntensity;
	GLfloat shininess;
};

