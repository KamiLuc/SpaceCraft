#pragma once

#include "../../Interfaces/EditableViaImGui.h"
#include "../../Settings/LightSettings.h"

#include <glm\glm.hpp>
#include <GL\glew.h>

using namespace Settings;

class Light : public EditableViaImGui
{
public:
	Light(const LightSettings& settings);
	Light(const glm::vec3& color, GLfloat ambiendIntenisty, GLfloat diffuseIntensity, const glm::vec3& direction);
	~Light();

	void setAmbientIntensity(GLfloat ambientIntensity);
	void setDirection(const glm::vec3& direction);

	void useLight(GLint ambientIntensityLocation, GLint colorLocation, GLint diffuseIntensityLocation, GLint directionLocation);

	void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID) override;

private:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
	glm::vec3 direction;
};

