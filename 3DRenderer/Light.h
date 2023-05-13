#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>

#include "../Settings/LightSettings.h"

using namespace Settings;

class Light
{
public:
	Light(const LightSettings& settings);
	~Light();

	void setAmbientIntensity(GLfloat ambientIntensity);
	void setDirection(const glm::vec3& direction);

	void useLight(GLint ambientIntensityLocation, GLint colorLocation, GLint diffuseIntensityLocation, GLint directionLocation);
	LightSettings* getSettings();

private:
	LightSettings settings;
};

