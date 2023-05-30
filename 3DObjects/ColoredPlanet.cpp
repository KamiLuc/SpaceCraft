#include "ColoredPlanet.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ColoredPlanet::ColoredPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass, const Measure<1>& radius,
	float scale, const std::string& identifier, const Shader& shader, const glm::vec4& color)
	:
	Planet(position, velocity, mass, radius, scale, identifier, shader),
	ColoredSphere(shader, color, 64, 64),
	Colored(color)
{
}

void ColoredPlanet::render(const UniformLocations& uniformLocations) const
{
	glm::mat4 model(1.0f);

	auto pos = position / worldScale3;
	auto sc = ((radius / worldScale1) * scale).getValuesInDesiredExponent(0)[0];

	model = glm::translate(model, pos.getGlmVec());
	model = glm::scale(model, glm::vec3(sc, sc, sc));
	model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformLocations.uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	ColoredSphere::render(uniformLocations);
}

void ColoredPlanet::editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID)
{
	ImGui::Begin(("Edit colored planet " + std::to_string(windowID)).c_str());

	Planet::editViaImGui(objectHandler, windowID);

	ImGui::Separator();
	if (ImGui::ColorEdit4("Planet color", glm::value_ptr(this->color), ImGuiColorEditFlags_Float | ImGuiColorEditFlags_AlphaBar)) {
		this->bindSingleColor(color);
	}
	ImGui::Separator();

	if (ImGui::Button("Close", { ImGui::GetWindowWidth(), 20 })) {
		objectHandler.removeObjectFromEdit(this);
	}
	ImGui::End();
}
