#include "RenderablePlanetObjectEditor.h"


RenderablePlanetObjectEditor::RenderablePlanetObjectEditor(
	const std::string& windowTitle, const ImVec2& windowMinSize, const ImVec2& windowMaxSize, TextureManager* texturedManager)
	: ObjectEditor(windowTitle, windowMinSize, windowMaxSize)
	, textureManager(texturedManager)
{
}

void RenderablePlanetObjectEditor::internalUpdate(EditableViaGui* object)
{
	ImGui::Separator();

	auto pp = dynamic_cast<TexturedPlanet*>(object);
	if (pp)
	{
		if (ImGui::BeginCombo("Texture", pp->getTexture()->getName().c_str()))
		{
			auto textures = textureManager->getTexturesNames();
			for (size_t i = 0; i < textures.size(); i++)
			{
				auto textureToDisplay = textureManager->getTexture(textures[i]);
				const bool isSelected = (pp->getTexture()->getName() == textures[i]);

				if (ImGui::Selectable(textures[i].c_str(), isSelected))
				{
					pp->setTexture(textureToDisplay);
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

		ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<intptr_t>(pp->getTexture()->getTextureId())),
					 ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1));
	}
}
