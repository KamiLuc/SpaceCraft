#pragma once

#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL\glew.h>

class Light
{
public:
	Light(const glm::vec3& color, GLfloat ambientIntenisty);
	virtual ~Light();

	glm::vec3 getColor() const;
	void setColor(const glm::vec3 color);
	GLfloat getAmbientIntensity() const;
	void setAmbientIntensity(GLfloat ambientIntensity);

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
};

