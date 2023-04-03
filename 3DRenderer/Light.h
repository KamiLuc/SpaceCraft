#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat xDirection, GLfloat yDirection, GLfloat zDirection, GLfloat diffuseIntensity);
	~Light();

	void setAmbientIntensity(GLfloat ambientIntensity);
	void setDirection(const glm::vec3& direction);

	void useLight(GLfloat ambientIntensityLocation, GLfloat colorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);

private:
	glm::vec3 color;
	GLfloat ambientIntensity;

	glm::vec3 direction;
	GLfloat diffuseIntensity;
};

