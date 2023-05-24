#include "ColoredPlanet.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

ColoredPlanet::ColoredPlanet(const glm::vec<3, Measure>& position, const glm::vec<3, Measure>& velocity,
	const Measure& mass, float scale, const std::string& identifier, const Shader& shader, const glm::vec4& color)
	:
	Planet(position, velocity, mass, scale, identifier, shader),
	ColoredSphere(shader, color, 32, 32),
	Colored(color)
{
}

void ColoredPlanet::render(const UniformLocations& uniformLocations) const
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
	model = glm::scale(model, glm::vec3(this->scale, this->scale, this->scale));
	model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformLocations.uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	ColoredSphere::render(uniformLocations);
}

bool ColoredPlanet::editViaImGui()
{
	ImGui::Begin("Edit colored planet");

	Planet::editViaImGui();

	ImGui::End();

	return true;
}
