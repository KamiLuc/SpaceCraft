#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "3DRenderer/Shader/UniformLocations.h"

class Light
{
public:
	Light(const glm::vec3& color, GLfloat ambientIntenisty);
	virtual ~Light();

	glm::vec3 getColor() const;
	GLfloat getAmbientIntensity() const;
	void setColor(const glm::vec3 color);
	void setAmbientIntensity(GLfloat ambientIntensity);

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
};

