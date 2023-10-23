#include "PointLight.h"

PointLight::PointLight()
	: PointLight({ 1.0f, 1.0f, 1.0f }, 0.5f, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f, 1.0f)
{
}

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

void PointLight::useLight(const UniformPointLight& uniformPointLight) const
{
	glUniform3f(uniformPointLight.color, color.r, color.g, color.b);
	glUniform3f(uniformPointLight.position, position.x, position.y, position.z);
	glUniform1f(uniformPointLight.ambientIntensity, ambientIntensity);
	glUniform1f(uniformPointLight.diffuseIntensity, diffuseIntensity);
	glUniform1f(uniformPointLight.exponent, exponent);
	glUniform1f(uniformPointLight.linear, linear);
	glUniform1f(uniformPointLight.constant, constant);
}
