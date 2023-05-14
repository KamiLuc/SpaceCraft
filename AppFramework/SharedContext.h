#pragma once

#include "Window.h"
#include "../3DRenderer/Shader/ShaderManager.h"
#include "../3DRenderer/Texture/TextureManager.h"

struct SharedContext
{
	SharedContext() : window(nullptr), eventManager(nullptr), shaderManager(nullptr) {}

	Window* window;
	EventManager* eventManager;
	ShaderManager* shaderManager;
	TextureManager* textureManager;
};