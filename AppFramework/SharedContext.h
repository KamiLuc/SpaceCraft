#pragma once

#include "Window.h"
#include "../3DRenderer/Shader/ShaderManager.h"
#include "../3DRenderer/Texture/TextureManager.h"

struct SharedContext
{
	SharedContext()
		: window(nullptr)
		, eventManager(nullptr)
		, shaderManager(nullptr)
		, textureManager(nullptr) {}

	Window* window;
	EventManager* eventManager;
	std::shared_ptr<ShaderManager> shaderManager;
	std::shared_ptr<TextureManager> textureManager;
};