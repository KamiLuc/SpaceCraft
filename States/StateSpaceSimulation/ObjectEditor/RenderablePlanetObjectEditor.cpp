#include "RenderablePlanetObjectEditor.h"

RenderablePlanetObjectEditor::RenderablePlanetObjectEditor(
	const std::string& windowTitle, const ImVec2& windowMinSize, const ImVec2& windowMaxSize, TextureManager* texturedManager)
	: ObjectEditor(windowTitle, windowMinSize, windowMaxSize)
	, textureManager(texturedManager)
{
}

void RenderablePlanetObjectEditor::registerDeleteObjectFunction(std::function<void(RenderablePlanet*)> func)
{
	deletePlanetFunction = func;
}

void RenderablePlanetObjectEditor::internalUpdate(EditableViaGui* object)
{
	auto texturedPlanetPtr = dynamic_cast<TexturedPlanet*>(object);
	if (texturedPlanetPtr)
	{
		if (ImGui::BeginCombo("Texture", texturedPlanetPtr->getTexture()->getName().c_str()))
		{
			auto textures = textureManager->getTexturesNames();
			for (size_t i = 0; i < textures.size(); i++)
			{
				auto textureToDisplay = textureManager->getTexture(textures[i]);
				const bool isSelected = (texturedPlanetPtr->getTexture()->getName() == textures[i]);

				if (ImGui::Selectable(textures[i].c_str(), isSelected))
				{
					texturedPlanetPtr->setTexture(textureToDisplay);
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

		ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<intptr_t>(texturedPlanetPtr->getTexture()->getTextureId())),
					 ImVec2(100, 100), ImVec2(0, 0), ImVec2(1, 1));
	}

	if (ImGui::Button("Delete", ImVec2(ImGui::GetContentRegionAvail().x, 20)) && deletePlanetFunction)
	{
		deletePlanetFunction(dynamic_cast<RenderablePlanet*>(object));
	}
}
