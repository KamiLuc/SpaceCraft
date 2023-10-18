#include "Light.h"

Light::Light(const glm::vec3& color, GLfloat ambientIntenisty)
	: color(color)
	, ambientIntensity(ambientIntenisty)
{
}

Light::~Light()
{
}

glm::vec3 Light::getColor() const
{
	return color;
}

void Light::setColor(const glm::vec3 color)
{
	this->color = color;
}

GLfloat Light::getAmbientIntensity() const
{
	return ambientIntensity;
}

void Light::setAmbientIntensity(GLfloat ambientIntensity)
{
	this->ambientIntensity = ambientIntensity;
}
