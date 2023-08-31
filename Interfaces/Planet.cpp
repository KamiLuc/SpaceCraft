#include "Planet.h"

void Planet::update(float timeInSec)
{
	if (canMove) {
		position += velocity * timeInSec;
	}
}

void Planet::editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID)
{
	ImGui::PushItemWidth(100.0f);
	std::array<const char*, 3> xyz{ "X", "Y", "Z" };
	std::array<const char*, 3> vxyz{ "vX", "vY", "vZ" };

	ImGui::Checkbox("Can move", &canMove);

	ImGui::Separator();
	ImGui::InputText("Identifier", const_cast<char*>(identifier.c_str()), sizeof(const_cast<char*>(identifier.c_str())));

	ImGui::Separator();
	ImGui::Text("Position settings");
	for (size_t i = 0; i < xyz.size(); ++i) {
		ImGui::DragFloat(xyz[i], position.getData()[i].getBasePtr(), 0.01f);
		ImGui::SameLine();
		std::string exponentLabel{ xyz[i] };
		exponentLabel += " Exponent";
		ImGui::InputInt(exponentLabel.c_str(), position.getData()[i].getExponentPtr());
	}

	ImGui::Separator();
	ImGui::Text("Velocity settings");
	for (size_t i = 0; i < vxyz.size(); ++i) {
		ImGui::DragFloat(vxyz[i], velocity.getData()[i].getBasePtr(), 0.01f);
		ImGui::SameLine();
		std::string exponentLabel{ vxyz[i] };
		exponentLabel += " Exponent";
		ImGui::InputInt(exponentLabel.c_str(), velocity.getData()[i].getExponentPtr());
	}

	ImGui::Separator();
	ImGui::DragFloat("Mass", mass.getBasePtr(), 0.01f, 0.0f, 1000.0f);
	ImGui::InputInt("Mass Exponent", mass.getExponentPtr());

	ImGui::Separator();
	ImGui::DragFloat("Radius", radius.getBasePtr(), 0.01f, 0.0f, 1000.0f);
	ImGui::InputInt("Radius Exponent", radius.getExponentPtr());

	ImGui::Separator();
	ImGui::DragFloat("Scale", &scale, 0.1f, 1.0f, 10000.0f);

	ImGui::Separator();
	ImGui::Text("Material settings");
	ImGui::DragFloat("Specular intensity", material.getSpecularIntensityPtr(), 0.01f, 0.0f, 1024.0f);
	ImGui::DragFloat("Shininess", material.getShininessPtr(), 0.01f, 0.0f, 1024.0f);
}