#pragma once

#include "AppFramework/GUI/ObjectEditor.h"
#include <3DObjects/TexturedPlanet.h>
#include "3DRenderer/Texture/TextureManager.h"

class RenderablePlanetObjectEditor : public ObjectEditor
{
public:
	RenderablePlanetObjectEditor(const std::string& windowTitle, const ImVec2& windowMinSize, const ImVec2& windowMaxSize, TextureManager* texturedManager);

private:
	void internalUpdate(EditableViaGui* object) override;

	TextureManager* textureManager;
};

