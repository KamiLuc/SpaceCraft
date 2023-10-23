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
