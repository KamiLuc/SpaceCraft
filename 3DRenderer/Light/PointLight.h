#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight(const glm::vec3& color, GLfloat ambientIntensity, const glm::vec3& position, GLfloat diffuseIntensity,
			   GLfloat exponent, GLfloat linear, GLfloat constant);
	virtual ~PointLight() {};

	void useLight(GLint colorLocation, GLint ambientIntensityLocation, GLint diffuseIntensityLocation, GLint positionLocation,
				  GLint exponentLocation, GLint linearLocation, GLint constantLocation);

private:
	glm::vec3 position;
	GLfloat diffuseIntensity;
	GLfloat constant;
	GLfloat linear;
	GLfloat exponent;
};

