#include "Light.h"

Light::Light() : Light(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f)
{
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat xDirection, GLfloat yDirection, GLfloat zDirection, GLfloat diffuseIntensity)
	: color(red, green, blue), ambientIntensity(ambientIntensity), direction(xDirection, yDirection, zDirection), diffuseIntensity(diffuseIntensity)
{
}

Light::~Light()
{
}

void Light::setAmbientIntensity(GLfloat ambientIntensity)
{
	this->ambientIntensity = ambientIntensity;
}

void Light::setDirection(const glm::vec3& direction)
{
	this->direction = direction;
}

void Light::useLight(GLint ambientIntensityLocation, GLint colorLocation, GLint diffuseIntensityLocation, GLint directionLocation)
{
	glUniform3f(colorLocation, this->color.r, this->color.g, this->color.b);
	glUniform1f(ambientIntensityLocation, this->ambientIntensity);

	glUniform3f(directionLocation, this->direction.x, this->direction.y, this->direction.z);
	glUniform1f(diffuseIntensityLocation, this->diffuseIntensity);
}
