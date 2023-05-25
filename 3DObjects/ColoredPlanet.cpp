#include "ColoredPlanet.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

ColoredPlanet::ColoredPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
	float scale, const std::string& identifier, const Shader& shader, const glm::vec4& color)
	:
	Planet(position, velocity, mass, scale, identifier, shader),
	ColoredSphere(shader, color, 64, 64),
	Colored(color)
{
}

void ColoredPlanet::render(const UniformLocations& uniformLocations) const
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, position.getGlmVec());
	model = glm::scale(model, glm::vec3(this->scale, this->scale, this->scale));
	model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformLocations.uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	ColoredSphere::render(uniformLocations);
}

void ColoredPlanet::editViaImGui(ImGuiEditableObjectsHandler* objectHandler, unsigned int windowID)
{
	ImGui::Begin(("Edit colored planet " + std::to_string(windowID)).c_str());

	Planet::editViaImGui(objectHandler, windowID);

	ImGui::Separator();
	if (ImGui::ColorPicker4("Planet color", glm::value_ptr(this->color), ImGuiColorEditFlags_Float | ImGuiColorEditFlags_AlphaBar)) {
		this->bindSingleColor(color);
	}
	ImGui::Separator();

	if (ImGui::Button("Close", { ImGui::GetWindowWidth(), 20 })) {
		objectHandler->removeObjectFromEdit(this);
	}
	ImGui::End();
}
