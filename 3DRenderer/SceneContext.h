#pragma once

#include <memory>

#include "Camera/CameraManagerToSFMLFrameworkAdapter.h"
#include "Light/OmnipresentLight.h"
#include "3DRenderer/Shader/ShaderManager.h"

struct SceneContext
{
public:
	SceneContext(
		std::shared_ptr<CameraManagerToSFMLFrameworkAdapter> cameraManager, std::shared_ptr<ShaderManager> shaderManager,
		std::shared_ptr<OmnipresentLight> mainLight)
		: mainLight(mainLight)
		, cameraManager(cameraManager)
		, shaderManager(shaderManager)
	{
	}

	SceneContext() : SceneContext(nullptr, nullptr, nullptr) {}
	std::shared_ptr<CameraManagerToSFMLFrameworkAdapter> cameraManager;
	std::shared_ptr<ShaderManager> shaderManager;
	std::shared_ptr<OmnipresentLight> mainLight;
};

