#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(const glm::vec3& color, GLfloat ambientIntenisty, GLfloat diffuseIntensity, const glm::vec3& direction);
	virtual ~DirectionalLight();

	void useLight(GLint colorLocation, GLint ambientIntensityLocation, GLint diffuseIntensityLocation, GLint directionLocation);

private:
	GLfloat diffuseIntensity;
	glm::vec3 direction;
};

