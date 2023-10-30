#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight();
	PointLight(const glm::vec3& color, GLfloat ambientIntensity, const glm::vec3& position, GLfloat diffuseIntensity,
			   GLfloat exponent, GLfloat linear, GLfloat constant);
	virtual ~PointLight() {};

	void useLight(const UniformPointLight& uniformPointLight) const;

protected:
	glm::vec3 position;
	GLfloat diffuseIntensity;
	GLfloat constant;
	GLfloat linear;
	GLfloat exponent;
};

