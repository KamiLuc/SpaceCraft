#include "TexturedPlanet.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

TexturedPlanet::TexturedPlanet(const Measure<3>& position, const Measure<3>& velocity,
	const Measure<1>& mass, float scale, const std::string& identifier, const Shader& shader, const Texture& texture)
	:
	Planet(position, velocity, mass, scale, identifier, shader),
	TexturedSphere(shader, texture, 64, 64)
{
}

void TexturedPlanet::render(const UniformLocations& uniformLocations) const
{
	glm::mat4 model(1.0f);
	model = glm::translate(model, position.getGlmVec());
	model = glm::scale(model, glm::vec3(this->scale, this->scale, this->scale));
	model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformLocations.uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	TexturedSphere::render(uniformLocations);
}

void TexturedPlanet::editViaImGui(ImGuiEditableObjectsHandler* objectHandler, unsigned int windowID)
{
	ImGui::Begin(("Edit textured planet " + std::to_string(windowID)).c_str());

	Planet::editViaImGui(objectHandler, windowID);

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
				ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));

			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	ImGui::Separator();
	ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<intptr_t>(this->texture->getTextureId())),
		ImVec2(100, 100), ImVec2(0, 1), ImVec2(1, 0));

	ImGui::Separator();
	if (ImGui::Button("Close", { ImGui::GetWindowWidth(), 20 })) {
		objectHandler->removeObjectFromEdit(this);
	}

	ImGui::End();
}
