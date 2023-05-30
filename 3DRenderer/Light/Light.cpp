#include "Light.h"

#include <glm/gtc/type_ptr.hpp>

Light::Light(const LightSettings& settings)
	: Light(settings.color, settings.ambientIntensity, settings.diffuseIntensity, settings.direction)
{
}

Light::Light(const glm::vec3& color, GLfloat ambientIntenisty, GLfloat diffuseIntensity, const glm::vec3& direction)
	: color(color)
	, ambientIntensity(ambientIntenisty)
	, diffuseIntensity(diffuseIntensity)
	, direction(direction)
{
}

Light::~Light()
{
}

void Light::setAmbientIntensity(GLfloat ambientIntensity)
{
	this->ambientIntensity = ambientIntensity;
}

void Light::setDirection(const glm::vec3& direction)
{
	this->direction = direction;
}

void Light::useLight(GLint ambientIntensityLocation, GLint colorLocation, GLint diffuseIntensityLocation, GLint directionLocation)
{
	glUniform3f(colorLocation, color.r, color.g, color.b);
	glUniform1f(ambientIntensityLocation, ambientIntensity);

	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

void Light::editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID)
{
	ImGui::Begin(("Edit light " + std::to_string(windowID)).c_str());

	ImGui::SliderFloat("Intensity", &ambientIntensity, 0.0f, 1.0f);
	ImGui::ColorEdit3("Color", glm::value_ptr(color), ImGuiColorEditFlags_Float);
	ImGui::Separator();

	ImGui::SliderFloat("Diffuse intensity", &diffuseIntensity, 0.0f, 1.0f);
	ImGui::Separator();

	ImGui::SliderFloat("X direction", &direction.x, -1.0f, 1.0f);
	ImGui::SliderFloat("Y direction", &direction.y, -1.0f, 1.0f);
	ImGui::SliderFloat("Z direction", &direction.z, -1.0f, 1.0f);

	ImGui::Separator();
	if (ImGui::Button("Close", { ImGui::GetWindowWidth(), 20 })) {
		objectHandler.removeObjectFromEdit(this);
	}

	ImGui::End();
}
