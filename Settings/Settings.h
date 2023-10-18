#pragma once

#include <filesystem>

#include "CameraSettings.h"
#include "LightSettings.h"

namespace Settings {

	class GlobalSettings
	{
	public:
		static GlobalSettings& getInstance()
		{
			static GlobalSettings instance;
			return instance;
		}

		GlobalSettings();
		~GlobalSettings() = default;
		GlobalSettings(const GlobalSettings&) = delete;
		GlobalSettings operator=(const GlobalSettings&) = delete;

		CameraSettings arcBallCameraSettings;
		CameraSettings firstPesonCameraSettings;
		MainLightSettings mainLightSettings;
		const std::filesystem::path texturesPath;
		const std::filesystem::path shadersPath;
		const std::filesystem::path savedSimulationsPath;
	};
}

