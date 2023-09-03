#pragma once

#include "../../3DRenderer/Shader/ShaderManager.h"
#include "../../3DRenderer/SceneContext.h"

#include <glm/glm.hpp>

class Renderable {
public:
	Renderable(std::shared_ptr<ShaderManager> shaderManager)
		: shaderManager(shaderManager)
	{
	};
	virtual ~Renderable() {}

	virtual void render(std::shared_ptr<SceneContext> sceneContext) const = 0;

	void setShaderManager(std::shared_ptr<ShaderManager> shaderManager) { this->shaderManager = shaderManager; }
	const std::shared_ptr<ShaderManager> getShaderManager() const { return shaderManager; }

protected:
	std::shared_ptr<ShaderManager> shaderManager;
};


