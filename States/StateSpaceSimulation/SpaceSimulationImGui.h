#pragma once

#include "../../Settings/CameraSettings.h" 
#include "../../Settings/LightSettings.h"

using namespace Settings;

class SpaceSimulationImGui
{
public:
	SpaceSimulationImGui(CameraSettings* arcBallCameraSettings, CameraSettings* fpsCameraSettings, LightSettings* mainLightSettings);
	void draw();

	bool shouldRenderCoordinateSystemAxis();

private:
	CameraSettings* fpsCameraSettings;
	CameraSettings* arcBallCameraSettings;
	LightSettings* mainLightSettings;

	bool renderCoordinateSystemAxis;

	void showFileMenu();
	void showSettingsMenu();
	void showObjectsMenu();
};

