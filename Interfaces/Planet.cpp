#include "Planet.h"

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

	ImGui::DragFloat3("Position", position.getValuesPtr(), 0.01f);
	ImGui::InputInt("Position exponent", position.getExponentPtr());
	ImGui::Separator();

	ImGui::DragFloat3("Velocity", velocity.getValuesPtr(), 0.01f);
	ImGui::InputInt("Velocity Exponent", velocity.getExponentPtr());
	ImGui::Separator();

	ImGui::DragFloat("Mass", mass.getValuesPtr(), 0.01f, 0.0f, 1000.0f);
	ImGui::InputInt("Mass Exponent", mass.getExponentPtr());
	ImGui::Separator();

	ImGui::DragFloat("Radius", radius.getValuesPtr(), 0.01f, 0.0f, 1000.0f);
	ImGui::InputInt("Radius Exponent", radius.getExponentPtr());
	ImGui::Separator();

	ImGui::DragFloat("Scale", &scale, 0.1f, 1.0f, 10000.0f);
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
	return (getPosition() / this->worldScale3).normalize();
}

Measure<1> Planet::getRadiusInWorldSpace() const
{
	return (this->radius / this->worldScale1).normalize() * this->scale;
}
