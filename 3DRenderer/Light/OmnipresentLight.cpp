#include "OmnipresentLight.h"

OmnipresentLight::OmnipresentLight(const glm::vec3& color, GLfloat ambientIntenisty)
	: Light(color, ambientIntenisty)
{
}

OmnipresentLight::~OmnipresentLight()
{
}

void OmnipresentLight::editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui)
{
	if (beginImGui)
	{
		ImGui::Begin(("Edit omnipresent light " + std::to_string(windowID)).c_str());
	}

	ImGui::SliderFloat("Intensity", &ambientIntensity, 0.0f, 1.0f);
	ImGui::ColorEdit3("Color", glm::value_ptr(color), ImGuiColorEditFlags_Float);

	ImGui::Separator();
	if (ImGui::Button("Close", { ImGui::GetWindowWidth(), 20 }))
	{
		objectHandler.removeObjectFromEdit(this);
	}

	if (beginImGui)
	{
		ImGui::End();
	}
}
