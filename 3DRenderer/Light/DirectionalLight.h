#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(const glm::vec3& color, GLfloat ambientIntenisty, GLfloat diffuseIntensity, const glm::vec3& direction);
	virtual ~DirectionalLight();

private:
	GLfloat diffuseIntensity;
	glm::vec3 direction;
};

