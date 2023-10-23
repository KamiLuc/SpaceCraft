#include "Settings.h"

namespace Settings {

	GlobalSettings::GlobalSettings()
		: shadersPath("Shaders")
		, texturesPath("Textures")
		, savedSimulationsPath("Simulations")
		, commonShaderCodePath("Shaders/CommonCode")
	{
		CameraSettings arcBall(5.0f, 1.0f, 0.0f, 0.0f, glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), "Arc ball camera");
		CameraSettings firstPerson(5.0f, 0.4f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), "First person camera");
		MainLightSettings mainLight({ 1.0f, 1.0f, 1.0f }, 0.5f);

		arcBallCameraSettings = std::move(arcBall);
		firstPesonCameraSettings = std::move(firstPerson);
		mainLightSettings = std::move(mainLight);
	}
}

