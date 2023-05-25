#include "Planet.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

void Planet::editViaImGui(ImGuiEditableObjectsHandler* objectHandler, unsigned int windowID)
{
	ImGui::InputText("Identifier", const_cast<char*>(identifier.c_str()), sizeof(const_cast<char*>(identifier.c_str())));
	ImGui::Separator();

	ImGui::InputFloat3("Position", position.getValuePtr());
	ImGui::InputInt("Position exponent", position.getExponentPtr());
	ImGui::Separator();

	ImGui::InputFloat3("Velocity", velocity.getValuePtr());
	ImGui::InputInt("Velocity Exponent", velocity.getExponentPtr());
	ImGui::Separator();

	ImGui::InputFloat("Mass", mass.getValuePtr());
	ImGui::InputInt("Mass Exponent", mass.getExponentPtr());
	ImGui::Separator();

	ImGui::SliderFloat("Scale", &scale, 0.01f, 10.0f);
	ImGui::Separator();
}
