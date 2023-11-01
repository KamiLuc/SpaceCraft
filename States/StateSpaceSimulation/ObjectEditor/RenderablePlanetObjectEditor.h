#pragma once

#include "AppFramework/GUI/ObjectEditor.h"
#include "Interfaces/RenderablePlanet.h"
#include "3DObjects/TexturedPlanet.h"
#include "3DRenderer/Texture/TextureManager.h"

class RenderablePlanetObjectEditor : public ObjectEditor
{
public:
	RenderablePlanetObjectEditor(const std::string& windowTitle, const ImVec2& windowMinSize, const ImVec2& windowMaxSize, TextureManager* texturedManager);

	void registerDeleteObjectFunction(std::function<void(RenderablePlanet*)> func);

private:
	void internalUpdate(EditableViaGui* object) override;

	std::function<void(RenderablePlanet*)> deletePlanetFunction;
	TextureManager* textureManager;
};

