#pragma once

#include "PlanetDistanceVisualizer.h"
#include "../SpaceSimulationSettings.h"
#include "../ObjectCreators/PlanetCreator.h"
#include "AppFramework/GUI/ObjectEditor.h"
#include "AppFramework/Serializer/Serializer.h"
#include "3DRenderer/Texture/TextureManager.h"

#include <array>
#include <vector>
#include <imgui.h>
#include <filesystem>
#include <boost/date_time/posix_time/posix_time.hpp>

class SpaceSimulationGUI
{
public:
	SpaceSimulationGUI(SpaceSimulationSettings& spaceSimulationSettings, PlanetCreator& planetCreator, Serializer& serializer, SceneContext& sceneContext);

	void draw();

private:
	ObjectEditor mainLightObjectEditor;
	ObjectEditor spaceSimulationSettingsObjectEditor;
	ObjectEditor planetDistanceVisualizerEditor;
	PlanetDistanceVisualizer planetDistanceVisualizer;

	SceneContext& sceneContext;
	PlanetCreator& planetCreator;
	Serializer& serializer;
	SpaceSimulationSettings& spaceSimulationSettings;

	std::vector<unsigned int> planetsToDelete;
	std::vector<std::filesystem::path> savedSimulations;

	void loadSavedSimulations();
	void drawEditors();

	void showFileMenu();
	void showSettingsMenu();
	void showObjectsMenu();
	void showToolsMenu();
	void showDeletePlanetsMenu();
	void showEditPlanetsMenu();
	void showObjectFocusMenu();
	void showSaveSimulationModal(const std::string& modal);
	void showLoadSimulationModal(const std::string& modal);

	void createColoredPlanet();
	void createTexturedPlanet();
	void createTexturedStar();
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
};

