#include "Settings.h"

namespace Settings {

	GlobalSettings::GlobalSettings()
		:
		shadersPath("Shaders"),
		texturesPath("Textures")
	{

		CameraSettings arcBall(5.0f, 1.0f, 0.0f, 0.0f, glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), "Arc ball camera");
		CameraSettings firstPerson(5.0f, 0.4f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), "First person camera");
		LightSettings mainLight({ 1.0f, 1.0f, 1.0f }, 0.5f, 0.0f, { 0.0f,0.0f,0.0f });

		arcBallCameraSettings = std::move(arcBall);
		firstPesonCameraSettings = std::move(firstPerson);
		mainLightSettings = std::move(mainLight);
	}

	CameraSettings GlobalSettings::getArcBallCameraSettings()
	{
		return arcBallCameraSettings;
	}

	CameraSettings GlobalSettings::getFirstPersonCameraSettings()
	{
		return firstPesonCameraSettings;
	}

	LightSettings GlobalSettings::getMainLightSettings()
	{
		return mainLightSettings;
	}

	std::filesystem::path GlobalSettings::getTexturesPath()
	{
		return texturesPath;
	}
	std::filesystem::path GlobalSettings::getShadersPath()
	{
		return shadersPath;
	}
}

