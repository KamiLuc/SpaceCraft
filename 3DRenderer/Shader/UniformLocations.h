#pragma once

#include <GL/glew.h>
#include <array>

constexpr auto MAX_POINT_LIGHTS = 124;

struct UniformOmnipresentLight
{
	GLuint color;
	GLuint ambientIntensity;

	UniformOmnipresentLight();
	UniformOmnipresentLight(GLuint uniformColor, GLuint uniformAmbientIntensity);
	void clear();
};

struct UniformPointLight
{
	GLuint color;
	GLuint ambientIntensity;
	GLuint diffuseIntensity;
	GLuint position;
	GLuint constant;
	GLuint linear;
	GLuint exponent;

	UniformPointLight();
	UniformPointLight(GLuint uniformColor, GLuint uniformAmbientIntensity, GLuint uniformDiffuseIntensity, GLuint uniformPosition,
					  GLuint uniformConstant, GLuint uniformLinear, GLuint uniformExponent);
	void clear();
};

struct UniformCamera
{
	GLuint projection;
	GLuint view;
	GLuint position;

	UniformCamera();
	UniformCamera(GLuint uniformProjection, GLuint uniformView, GLuint uniformPosition);
	void clear();
};

struct UniformMaterial
{
	GLuint specularIntensity;
	GLuint shininess;

	UniformMaterial();
	UniformMaterial(GLuint specularIntensity, GLuint Shininess);
	void clear();
};

struct UniformLocations
{
	GLuint model;
	GLuint worldScale;
	GLuint orbitColor;
	GLuint timePassed;
	GLuint objectOnScreenPosition;

	UniformMaterial material;
	UniformCamera camera;
	UniformOmnipresentLight omnipresentLight;

	GLuint pointLightCount;
	std::array<UniformPointLight, MAX_POINT_LIGHTS> pointLights;

	UniformLocations();
	void clear();
};