#include "ColoredPlanet.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ColoredPlanet::ColoredPlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
	float scale, const std::string& identifier, std::shared_ptr<ShaderManager> shaderManager, const glm::vec4& color)
	: RenderablePlanet(position, velocity, mass, radius, scale, identifier, shaderManager)
	, Colored(color)
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

void ColoredPlanet::render(std::shared_ptr<SceneContext> sceneContext) const
{
	auto shader = shaderManager->getShader("coloredObjectShader");
	auto& uniforms = shader->getUniformLocations();

	if (shader != shaderManager->getLastUsedShader())
	{
		shader->useShader();
		shaderManager->setLastUsedShader(shader);
	}

	sceneContext->cameraManager->useCamera(uniforms.uniformView, uniforms.uniformCameraPosition, uniforms.uniformProjection);
	sceneContext->mainLight->useLight(uniforms.uniformAmbientIntensity, uniforms.uniformAmbientColor, uniforms.uniformDiffuseIntensity, uniforms.uniformLightDirection);
	material.useMaterial(uniforms.uniformSpecularIntensity, uniforms.uniformShininess);

	glUniformMatrix4fv(uniforms.uniformModel, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));
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

