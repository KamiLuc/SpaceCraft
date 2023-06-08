#include "Planet.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

void Planet::update(float timeInSec)
{
	if (this->canMove) {
		this->position += this->velocity * timeInSec;
	}
}

void Planet::editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID)
{
	ImGui::Checkbox("Can move", &this->canMove);
	ImGui::Separator();

	ImGui::InputText("Identifier", const_cast<char*>(identifier.c_str()), sizeof(const_cast<char*>(identifier.c_str())));
	ImGui::Separator();

	ImGui::InputFloat3("Position", position.getValuesPtr());
	ImGui::InputInt("Position exponent", position.getExponentPtr());
	ImGui::Separator();

	ImGui::InputFloat3("Velocity", velocity.getValuesPtr());
	ImGui::InputInt("Velocity Exponent", velocity.getExponentPtr());
	ImGui::Separator();

	ImGui::InputFloat("Mass", mass.getValuesPtr());
	ImGui::InputInt("Mass Exponent", mass.getExponentPtr());
	ImGui::Separator();

	ImGui::InputFloat("Radius", radius.getValuesPtr());
	ImGui::InputInt("Radius Exponent", radius.getExponentPtr());
	ImGui::Separator();

	ImGui::SliderFloat("Scale", &scale, 0.01f, 100.0f);
	ImGui::Separator();

	if (ImGui::Button("Normalize values")) {
		position.normalize();
		velocity.normalize();
		mass.normalize();
		radius.normalize();
	}
}

Measure<3> Planet::getPositionInWorldSpace() const
{
	return getPosition() / this->worldScale3;
}
