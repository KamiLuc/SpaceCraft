#include "UniformLocations.h"

UniformLocations::UniformLocations()
	: model(0)
	, worldScale(0)
	, orbitColor(0)
	, pointLightCount(0)
	, omnipresentLight(0, 0)
{
}

void UniformLocations::clear()
{
	model = 0;
	worldScale = 0;
	orbitColor = 0;
	pointLightCount = 0;
	omnipresentLight.clear();
	camera.clear();
	material.clear();

	for (auto& el : pointLights)
	{
		el.clear();
	}
}

UniformPointLight::UniformPointLight()
	: UniformPointLight(0, 0, 0, 0, 0, 0, 0)
{
}

UniformPointLight::UniformPointLight(GLuint uniformColor, GLuint uniformAmbientIntensity, GLuint uniformDiffuseIntensity,
									 GLuint uniformPosition, GLuint uniformConstant, GLuint uniformLinear, GLuint uniformExponent)
	: color(uniformColor)
	, ambientIntensity(uniformAmbientIntensity)
	, diffuseIntensity(uniformDiffuseIntensity)
	, position(uniformPosition)
	, constant(uniformConstant)
	, linear(uniformLinear)
	, exponent(uniformExponent)
{

}

void UniformPointLight::clear()
{
	color = 0;
	ambientIntensity = 0;
	diffuseIntensity = 0;
	position = 0;
	constant = 0;
	linear = 0;
	exponent = 0;
}

UniformOmnipresentLight::UniformOmnipresentLight()
	: UniformOmnipresentLight(0, 0)
{
}

UniformOmnipresentLight::UniformOmnipresentLight(GLuint uniformColor, GLuint uniformAmbientIntensity)
	: color(uniformColor)
	, ambientIntensity(uniformAmbientIntensity)
{
}

void UniformOmnipresentLight::clear()
{
	color = 0;
	ambientIntensity = 0;
}

UniformCamera::UniformCamera()
	: UniformCamera(0, 0, 0)
{
}

UniformCamera::UniformCamera(GLuint uniformProjection, GLuint uniformView, GLuint uniformPosition)
	: projection(uniformProjection)
	, view(uniformView)
	, position(uniformPosition)
{
}

void UniformCamera::clear()
{
	projection = 0;
	view = 0;
	position = 0;
}

UniformMaterial::UniformMaterial()
	: UniformMaterial(0, 0)
{
}

UniformMaterial::UniformMaterial(GLuint specularIntensity, GLuint shininess)
	: specularIntensity(specularIntensity)
	, shininess(shininess)
{
}

void UniformMaterial::clear()
{
	specularIntensity = 0;
	shininess = 0;
}
