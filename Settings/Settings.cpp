#include "Settings.h"

namespace Settings {

	GlobalSettings::GlobalSettings() {

		CameraSettings arcBall(5.0f, 1.0f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), "Arc ball camera");
		CameraSettings firstPerson(5.0f, 0.4f, 0.0f, 0.0f, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), "First person camera");

		arcBallCameraSettings = std::move(arcBall);
		firstPesonCameraSettings = std::move(firstPerson);
	}

	CameraSettings* GlobalSettings::getArcBallCameraSettings()
	{
		return &arcBallCameraSettings;
	}
	CameraSettings* GlobalSettings::getFirstPersonCameraSettings()
	{
		return &firstPesonCameraSettings;
	}
}

