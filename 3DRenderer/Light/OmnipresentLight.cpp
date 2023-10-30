#include "OmnipresentLight.h"

OmnipresentLight::OmnipresentLight(const glm::vec3& color, GLfloat ambientIntenisty)
	: Light(color, ambientIntenisty)
{
}

void OmnipresentLight::editViaGui()
{
	ImGui::SliderFloat("Intensity", &ambientIntensity, 0.0f, 1.0f);
	ImGui::ColorEdit3("Color", glm::value_ptr(color), ImGuiColorEditFlags_Float);
}
