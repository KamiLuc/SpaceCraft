#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3& color, GLfloat ambientIntenisty, GLfloat diffuseIntensity, const glm::vec3& direction)
	: Light(color, ambientIntenisty)
	, diffuseIntensity(diffuseIntensity)
	, direction(direction)
{
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::useLight(GLint colorLocation, GLint ambientIntensityLocation, GLint diffuseIntensityLocation, GLint directionLocation)
{
	glUniform3f(colorLocation, color.r, color.g, color.b);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}
