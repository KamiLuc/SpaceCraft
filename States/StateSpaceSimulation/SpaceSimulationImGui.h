#pragma once

#include "../../Settings/CameraSettings.h" 
#include "../../Settings/LightSettings.h"
#include "../../3DRenderer/Texture/TextureManager.h"
#include "../../3DObjects/Interfaces/Planet.h"
#include "../../3DObjects/Interfaces/ImGuiEditableObjectsHandler.h"
#include "StateSpaceSimulation.h"

#include <vector>

using namespace Settings;

class StateSpaceSimulation;

class SpaceSimulationImGui : public ImGuiEditableObjectsHandler
{
public:
	SpaceSimulationImGui(StateSpaceSimulation& spaceSimulation, CameraSettings* arcBallCameraSettings, CameraSettings* fpsCameraSettings,
		LightSettings* mainLightSettings, TextureManager& textureManager);
	void draw();

	bool shouldRenderCoordinateSystemAxis();

	void createPreviewColoredPlanet();
	void createPreviewTexturedPlanet();

private:
	StateSpaceSimulation& spaceSimulation;
	CameraSettings* fpsCameraSettings;
	CameraSettings* arcBallCameraSettings;
	LightSettings* mainLightSettings;
	TextureManager& textureManager;
	std::vector<std::shared_ptr<Planet>> previewPlanets;

	bool renderCoordinateSystemAxis;

	void showFileMenu();
	void showSettingsMenu();
	void showObjectsMenu();
};

