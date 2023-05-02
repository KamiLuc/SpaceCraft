#pragma once

#include "CameraSettings.h"

namespace Settings {

	class GlobalSettings
	{
	public:
		static GlobalSettings& getInstance() {
			static GlobalSettings instance;
			return instance;
		}

		CameraSettings* getArcBallCameraSettings();
		CameraSettings* getFirstPersonCameraSettings();

	private:
		GlobalSettings();
		~GlobalSettings() = default;
		GlobalSettings(const GlobalSettings&) = delete;
		GlobalSettings operator=(const GlobalSettings&) = delete;

		CameraSettings arcBallCameraSettings;
		CameraSettings firstPesonCameraSettings;
	};
}

