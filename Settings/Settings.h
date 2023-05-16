#pragma once

#include <filesystem>

#include "CameraSettings.h"
#include "LightSettings.h"

namespace Settings {

	class GlobalSettings
	{
	public:
		static GlobalSettings& getInstance() {
			static GlobalSettings instance;
			return instance;
		}

		CameraSettings getArcBallCameraSettings();
		CameraSettings getFirstPersonCameraSettings();
		LightSettings getMainLightSettings();
		std::filesystem::path getTexturesPath();
		std::filesystem::path getShadersPath();

	private:
		GlobalSettings();
		~GlobalSettings() = default;
		GlobalSettings(const GlobalSettings&) = delete;
		GlobalSettings operator=(const GlobalSettings&) = delete;

		CameraSettings arcBallCameraSettings;
		CameraSettings firstPesonCameraSettings;
		LightSettings mainLightSettings;

		const std::filesystem::path texturesPath;
		const std::filesystem::path shadersPath;
	};
}

