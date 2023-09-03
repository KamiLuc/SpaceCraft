#pragma once

#include "../../Settings/CameraSettings.h" 
#include "../../Settings/LightSettings.h"
#include "../../3DRenderer/Texture/TextureManager.h"
#include "../../Interfaces/Planet.h"
#include "../../Interfaces/ImGuiEditableObjectsHandler.h"
#include "StateSpaceSimulation.h"

#include <vector>
#include <imgui.h>
#include <array>

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
	void showDeletePlanetsMenu();
	void showEditPlanetsMenu();
	void showObjectFocusMenu();

	virtual void deleteObject(std::shared_ptr<EditableViaImGui> object);
	virtual void deleteObject(EditableViaImGui* object);
};

