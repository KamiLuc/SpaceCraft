#pragma once

#include "Settings/CameraSettings.h" 
#include "Settings/LightSettings.h"
#include "3DRenderer/Texture/TextureManager.h"
#include "Interfaces/Planet.h"
#include "AppFramework/GUI/EditableViaImGui.h"
#include "../StateSpaceSimulation.h"

#include <vector>
#include <imgui.h>
#include <array>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace Settings;

class StateSpaceSimulation;

class SpaceSimulationImGui : public ImGuiEditableObjectsHandler
{
public:
	SpaceSimulationImGui(StateSpaceSimulation& spaceSimulation, TextureManager& textureManager);

	void draw();

private:
	StateSpaceSimulation& spaceSimulation;
	TextureManager& textureManager;
	std::vector<unsigned int> planetsToDelete;
	std::vector<std::string> savedSimulations;
	bool renderCoordinateSystemAxis;

	void showFileMenu();
	void showSettingsMenu();
	void showObjectsMenu();
	void showDeletePlanetsMenu();
	void showEditPlanetsMenu();
	void showObjectFocusMenu();
	void showSaveSimulationModal(const std::string& modal);
	void showLoadSimulationModal(const std::string& modal);

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

	void loadSavedSimulations();

	virtual void deleteObject(std::shared_ptr<EditableViaImGui> object) override;
	virtual void deleteObject(EditableViaImGui* object) override;
};

