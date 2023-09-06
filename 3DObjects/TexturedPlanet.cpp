#include "TexturedPlanet.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TexturedPlanet::TexturedPlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
							   const PhysicalUnit& radius, float scale, const std::string& identifier, std::shared_ptr<ShaderManager> shaderManager, const Texture& texture)
	: RenderablePlanet(position, velocity, mass, radius, scale, identifier, shaderManager)
	, Textured(texture)
{
	std::vector<GLfloat> vertices {};
	std::vector<GLfloat> normals {};
	std::vector<GLfloat> textureCoordinates {};
	std::vector<unsigned int> indices {};

	for (GLuint i = 0; i <= stacks; ++i)
	{
		for (GLuint j = 0; j <= sectors; ++j)
		{
			textureCoordinates.emplace_back(static_cast<GLfloat>(j) / sectors);
			textureCoordinates.emplace_back(static_cast<GLfloat>(i) / stacks);
		}
	}

	Sphere::createSphere(vertices, normals, indices);
	this->mesh.createMesh(vertices, indices, normals, textureCoordinates);

}

void TexturedPlanet::render(std::shared_ptr<SceneContext> sceneContext) const
{
	auto shader = shaderManager->getShader("texturedObjectShader");
	auto& uniforms = shader->getUniformLocations();

	if (shader != shaderManager->getLastUsedShader())
	{
		shader->useShader();
		shaderManager->setLastUsedShader(shader);
	}

	sceneContext->cameraManager->useCamera(uniforms.uniformView, uniforms.uniformCameraPosition, uniforms.uniformProjection);
	sceneContext->mainLight->useLight(uniforms.uniformAmbientIntensity, uniforms.uniformAmbientColor, uniforms.uniformDiffuseIntensity, uniforms.uniformLightDirection);
	material.useMaterial(uniforms.uniformSpecularIntensity, uniforms.uniformShininess);

	texture->useTexture();
	glUniformMatrix4fv(uniforms.uniformModel, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));
	mesh.useMesh();

	if (renderOrbit)
	{
		orbitInWorldSpace.render(sceneContext);
	}
}

void TexturedPlanet::editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui)
{
	if (beginImGui)
	{
		ImGui::SetNextWindowSizeConstraints(ImVec2(410, 300), ImVec2(410, 1000));
		ImGui::Begin(("Edit textured planet " + std::to_string(windowID)).c_str(), nullptr);
	}

	RenderablePlanet::editViaImGui(objectHandler, windowID, false);

	ImGui::Separator();
	if (ImGui::BeginCombo("Texture", texture->getName().c_str()))
	{
		auto& tm = texture->getTextureManager();
		auto textures = tm.getTexturesNames();
		for (size_t i = 0; i < textures.size(); i++)
		{
			auto textureToDisplay = tm.getTexture(textures[i]);
			const bool isSelected = (texture->getName() == textures[i]);

			if (ImGui::Selectable(textures[i].c_str(), isSelected))
			{
				texture = textureToDisplay.get();
			}

			ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<intptr_t>(textureToDisplay->getTextureId())),
						 ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1));

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<intptr_t>(this->texture->getTextureId())),
				 ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1));

	ImGui::Separator();
	if (ImGui::Button("Close", { ImGui::GetWindowWidth() / 2, 20 }))
	{
		objectHandler.removeObjectFromEdit(this);
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete planet", { ImGui::GetWindowWidth() / 2, 20 }))
	{
		objectHandler.deleteObject(this);
	}

	if (beginImGui)
	{
		ImGui::End();
	}
}
