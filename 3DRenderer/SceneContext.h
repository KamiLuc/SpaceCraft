#pragma once

#include <memory>

#include "Camera/CameraManagerToSFMLFrameworkAdapter.h"
#include "Light/OmnipresentLight.h"
#include "Light/PointLight.h"
#include "3DRenderer/Shader/ShaderManager.h"

struct SceneContext
{
public:
	SceneContext(
		std::shared_ptr<CameraManagerToSFMLFrameworkAdapter> cameraManager, std::shared_ptr<ShaderManager> shaderManager,
		std::shared_ptr<OmnipresentLight> mainLight, float lastUpdateInSec = 0.0f)
		: mainLight(mainLight)
		, cameraManager(cameraManager)
		, shaderManager(shaderManager)
		, lastUpdateInSec(lastUpdateInSec)
	{
	}

	SceneContext()
		: SceneContext(nullptr, nullptr, nullptr)
	{
	}
	std::shared_ptr<CameraManagerToSFMLFrameworkAdapter> cameraManager;
	std::shared_ptr<ShaderManager> shaderManager;
	std::shared_ptr<OmnipresentLight> mainLight;
	std::list<std::shared_ptr<PointLight>> pointLights;
	float lastUpdateInSec;
};

