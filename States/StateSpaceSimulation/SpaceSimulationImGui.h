#pragma once

#include "../../Settings/CameraSettings.h" 
#include "../../Settings/LightSettings.h"
#include "../../3DRenderer/Texture/TextureManager.h"
#include "../../Utils/Measure.h"
#include "../../3DObjects/Interfaces/Planet.h"
#include "StateSpaceSimulation.h"

#include <vector>

using namespace Settings;

class StateSpaceSimulation;

class SpaceSimulationImGui
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

	bool renderCoordinateSystemAxis;

	std::vector<std::string> textures;
	std::shared_ptr<Planet> previewPlanet;
	int objectToEditIndex;
	int newObjectTextureIndex;
	float newObjectColor[4];
	float newObjectPosition[3];
	int newObjectPositionExponent;
	float newObjectVelocity[3];
	int newObjectVelocityExponent;
	float newObjectMass;
	int newObjectMassExponent;
	float newObjectScale;
	char newObjectIdentifier[256];
	char newObjectTexture[256];
	bool b_showCreateTexturedPlanetWindow;
	bool b_showCreateColoredPlanetWindow;

	void showFileMenu();
	void showBaseCreatePlanet();
	void showCreateTexturedPlanetWindow();
	void showCreateColoredPlanetWindow();
	void showSettingsMenu();
	void showObjectsMenu();
};

