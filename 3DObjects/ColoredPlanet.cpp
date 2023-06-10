#include "ColoredPlanet.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ColoredPlanet::ColoredPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass, const Measure<1>& radius,
	float scale, const std::string& identifier, const Shader& shader, const glm::vec4& color)
	: Planet(position, velocity, mass, radius, scale, identifier)
	, Colored(color)
	, Renderable(shader)
{
	std::vector<GLfloat> vertices{};
	std::vector<GLfloat> normals{};
	std::vector<unsigned int> indices{};
	std::vector<GLfloat> colors((stacks + 1) * (sectors + 1) * 4);

	for (size_t i = 0; i < colors.size() / 4; i += 1) {
		colors[i * 4] = color[0];
		colors[i * 4 + 1] = color[1];
		colors[i * 4 + 2] = color[2];
		colors[i * 4 + 3] = color[3];
	}

	Sphere::createSphere(vertices, normals, indices);
	this->mesh.createMesh(vertices, indices, normals, colors);
}

void ColoredPlanet::render(const UniformLocations& uniformLocations) const
{
	glUniformMatrix4fv(uniformLocations.uniformModel, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));
	mesh.useMesh();
}

void ColoredPlanet::editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID)
{
	ImGui::Begin(("Edit colored planet " + std::to_string(windowID)).c_str());

	Planet::editViaImGui(objectHandler, windowID);

	ImGui::Separator();
	if (ImGui::ColorEdit4("Planet color", glm::value_ptr(this->color), ImGuiColorEditFlags_Float | ImGuiColorEditFlags_AlphaBar)) {
		mesh.bindSingleColor(color);
	}
	ImGui::Separator();

	if (ImGui::Button("Close", { ImGui::GetWindowWidth() / 2, 20 })) {
		objectHandler.removeObjectFromEdit(this);
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete planet", { ImGui::GetWindowWidth() / 2, 20 })) {
		objectHandler.deleteObject(this);
	}

	ImGui::End();
}

glm::mat4 ColoredPlanet::getModelMatrix() const
{
	glm::mat4 model(1.0f);

	auto pos = position / worldScale3;
	auto sc = ((radius / worldScale1) * scale).getValuesInDesiredExponent(0)[0];

	model = glm::translate(model, pos.getGlmVec());
	model = glm::scale(model, glm::vec3(sc, sc, sc));
	model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	return model;
}
