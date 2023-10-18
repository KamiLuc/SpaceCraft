#include "PointLight.h"

PointLight::PointLight(const glm::vec3& color, GLfloat ambientIntensity, const glm::vec3& position, GLfloat diffuseIntensity,
					   GLfloat exponent, GLfloat linear, GLfloat constant)
	: Light(color, ambientIntensity)
	, position(position)
	, diffuseIntensity(diffuseIntensity)
	, exponent(exponent)
	, linear(linear)
	, constant(constant)
{
}

void PointLight::useLight(GLint colorLocation, GLint ambientIntensityLocation, GLint diffuseIntensityLocation, GLint positionLocation,
						  GLint exponentLocation, GLint linearLocation, GLint constantLocation)
{
	glUniform3f(colorLocation, color.r, color.g, color.b);
	glUniform3f(positionLocation, position.x, position.y, position.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform1f(exponentLocation, exponent);
	glUniform1f(linearLocation, linear);
	glUniform1f(constantLocation, constant);
}
