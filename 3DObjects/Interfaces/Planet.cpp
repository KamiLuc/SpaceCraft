#include "Planet.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

bool Planet::editViaImGui()
{
	ImGui::InputText("Identifier", const_cast<char*>(identifier.c_str()), sizeof(const_cast<char*>(identifier.c_str())));
	ImGui::Separator();

	float position[3]{ this->position.x, this->position.y, this->position.z };
	ImGui::InputFloat3("Position", position);
	ImGui::InputInt("Exponent", this->position.x.getExponentPtr());
	this->setPosition({ {position[0], 1}, { position[1], 1 }, { position[2], 1 } });
	//previewPlanet->setPosition(glm::vec3(newObjectPosition[0], newObjectPosition[1], newObjectPosition[2]), newObjectPositionExponent);
	//ImGui::Separator();

	/*
	ImGui::InputFloat3("Velocity", newObjectVelocity);
	ImGui::InputInt("Velocity", &newObjectVelocityExponent);
	ImGui::Separator();

	ImGui::InputFloat("Mass", &newObjectMass);
	ImGui::InputInt("Mass", &newObjectMassExponent);
	previewPlanet->setMass({ newObjectMass, newObjectMassExponent });
	ImGui::Separator();

	ImGui::SliderFloat("Scale", &newObjectScale, 0.01f, 10.0f);
	previewPlanet->setScale(newObjectScale);
	ImGui::Separator();
	*/
	return true;
}
