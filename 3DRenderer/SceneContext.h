#pragma once

#include <memory>

#include "Camera/CameraManagerToSFMLFrameworkAdapter.h"
#include "Light/Light.h"
#include "3DRenderer/Material.h"
#include "3DRenderer/Shader/ShaderManager.h"

struct SceneContext
{
public:
	SceneContext(
		std::shared_ptr<CameraManagerToSFMLFrameworkAdapter> cameraManager, std::shared_ptr<ShaderManager> shaderManager,
		std::shared_ptr<Light> mainLight, std::shared_ptr<Material> material)
		: mainLight(mainLight)
		, cameraManager(cameraManager)
		, defaultMaterial(material)
		, shaderManager(shaderManager)
	{
	}

	SceneContext() : SceneContext(nullptr, nullptr, nullptr, nullptr) {}
	std::shared_ptr<CameraManagerToSFMLFrameworkAdapter> cameraManager;
	std::shared_ptr<ShaderManager> shaderManager;
	std::shared_ptr<Light> mainLight;
	std::shared_ptr<Material> defaultMaterial;
};

