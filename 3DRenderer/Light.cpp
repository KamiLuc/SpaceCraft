#include "Light.h"

Light::Light(const LightSettings& settings)
	: settings(settings)
{
}

Light::~Light()
{
}

void Light::setAmbientIntensity(GLfloat ambientIntensity)
{
	settings.ambientIntensity = ambientIntensity;
}

void Light::setDirection(const glm::vec3& direction)
{
	settings.direction = direction;
}

void Light::useLight(GLint ambientIntensityLocation, GLint colorLocation, GLint diffuseIntensityLocation, GLint directionLocation)
{
	glUniform3f(colorLocation, settings.color.r, settings.color.g, settings.color.b);
	glUniform1f(ambientIntensityLocation, settings.ambientIntensity);

	glUniform3f(directionLocation, settings.direction.x, settings.direction.y, settings.direction.z);
	glUniform1f(diffuseIntensityLocation, settings.diffuseIntensity);
}

LightSettings* Light::getSettings()
{
	return &settings;
}
