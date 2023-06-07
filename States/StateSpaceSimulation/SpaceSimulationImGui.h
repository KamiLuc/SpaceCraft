#pragma once

#include "../../Settings/CameraSettings.h" 
#include "../../Settings/LightSettings.h"
#include "../../3DRenderer/Texture/TextureManager.h"
#include "../../Interfaces/Planet.h"
#include "../../Interfaces/ImGuiEditableObjectsHandler.h"
#include "StateSpaceSimulation.h"

#include <vector>

using namespace Settings;

class StateSpaceSimulation;

class SpaceSimulationImGui : public ImGuiEditableObjectsHandler
{
public:
	SpaceSimulationImGui(StateSpaceSimulation& spaceSimulation, TextureManager& textureManager);
	void draw();

	void createColoredPlanet();
	void createTexturedPlanet();

	void createSolarSystem();

	void createEarth();
	void createSun();
	void createMercury();
	void createVenus();
	void createJupiter();
	void createSaturn();
	void createUranus();
	void createNeptune();
	void createMars();

private:
	StateSpaceSimulation& spaceSimulation;
	TextureManager& textureManager;

	std::vector<unsigned int> planetsToDelete;

	bool renderCoordinateSystemAxis;

	void showFileMenu();
	void showSettingsMenu();
	void showObjectsMenu();
	void showDestroyPlanetsMenu();
	void showEditPlanetsMenu();
};

