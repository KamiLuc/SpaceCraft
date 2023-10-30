#include "Settings.h"

namespace Settings {

	GlobalSettings::GlobalSettings()
		: shadersPath("Shaders")
		, texturesPath("Textures")
		, skyboxTexturesPath("Textures/Skybox")
		, savedSimulationsPath("Simulations")
		, commonShaderCodePath("Shaders/CommonCode")
		, windowWidth(1620)
		, windowHeight(900)
	{
		CameraSettings arcBall(5.0f, 1.0f, 0.0f, 0.0f, glm::vec3(20.0f, 10.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), "Arc ball camera");
		CameraSettings firstPerson(5.0f, 0.4f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), "First person camera");
		MainLightSettings mainLight({ 1.0f, 1.0f, 1.0f }, 0.1f);

		arcBallCameraSettings = std::move(arcBall);
		firstPesonCameraSettings = std::move(firstPerson);
		mainLightSettings = std::move(mainLight);
	}
}

