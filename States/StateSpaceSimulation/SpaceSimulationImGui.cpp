#include "SpaceSimulationImGui.h"
#include <imgui.h>
#include <vector>

SpaceSimulationImGui::SpaceSimulationImGui(StateSpaceSimulation& spaceSimulation, TextureManager& textureManager)
	: spaceSimulation(spaceSimulation)
	, textureManager(textureManager)
	, renderCoordinateSystemAxis(false) {}

void SpaceSimulationImGui::draw()
{
	this->update();

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			showFileMenu();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Settings")) {
			showSettingsMenu();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Objects")) {
			showObjectsMenu();
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void SpaceSimulationImGui::createColoredPlanet()
{
	auto temp = this->spaceSimulation.createColoredPlanet(
		{ {0.0f, 0.0f, 0.0f}, 0 },
		{ {0.0f, 0.0f, 0.0f}, 0 },
		0.0f,
		1.0f,
		1.0f,
		"Planet",
		{ 0.3f, 0.2f, 0.8f, 1.0f });

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::createTexturedPlanet()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {0.0f, 0.0f, 0.0f}, 0 },
		{ {0.0f, 0.0f, 0.0f}, 0 },
		0.0f,
		1.0f,
		1.0f,
		"Planet",
		*this->textureManager.getTexture(this->textureManager.getTexturesNames()[0]));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::createSolarSystem()
{
	createSun();
	createMercury();
	createVenus();
	createEarth();
	createMars();
	createJupiter();
	createSaturn();
	createUranus();
	createNeptune();

	objectsToEdit.clear();
}

void SpaceSimulationImGui::createEarth()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {1.496f, 0.0f, 0.0f}, 11 },
		{ {0.0f, 0.0f, 2.978f}, 4 },
		{ 5.972f, 24 },
		{ 6.371f, 6 },
		1.0f,
		"Earth",
		*this->textureManager.getTexture("earth"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::createSun()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {0.0f, 0.0f, 0.0f}, 11 },
		{ {0.0f, 0.0f, 0.0f}, 4 },
		{ 1.989f, 30 },
		{ 6.963f, 8 },
		1.0f,
		"Sun",
		*this->textureManager.getTexture("sun"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::createMercury()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {5.791f, 0.0f, 0.0f}, 10 },
		{ {0.0f, 0.0f, 4.736f}, 4 },
		{ 3.285f, 23 },
		{ 2.439f, 6 },
		1.0f,
		"Mercury",
		*this->textureManager.getTexture("mercury"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::createVenus()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {1.082f, 0.0f, 0.0f}, 11 },
		{ {0.0f, 0.0f, 3.502f}, 4 },
		{ 4.867f, 24 },
		{ 6.051f, 6 },
		1.0f,
		"Venus",
		*this->textureManager.getTexture("venus"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::createJupiter()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {7.785f, 0.0f, 0.0f}, 11 },
		{ {0.0f, 0.0f, 1.307f}, 4 },
		{ 1.898f, 27 },
		{ 6.699f, 6 },
		1.0f,
		"Jupiter",
		*this->textureManager.getTexture("jupiter"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::createSaturn()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {1.427f, 0.0f, 0.0f}, 12 },
		{ {0.0f, 0.0f, 9.672f}, 3 },
		{ 5.683f, 26 },
		{ 5.823f, 7 },
		1.0f,
		"Saturn",
		*this->textureManager.getTexture("saturn"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::createUranus()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {2.871f, 0.0f, 0.0f}, 12 },
		{ {0.0f, 0.0f, 6.81f}, 3 },
		{ 8.681f, 25 },
		{ 2.536f, 7 },
		1.0f,
		"Uranus",
		*this->textureManager.getTexture("uranus"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::createNeptune()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {4.498f, 0.0f, 0.0f}, 12 },
		{ {0.0f, 0.0f, 5.43f}, 3 },
		{ 1.024f, 26 },
		{ 2.462f, 7 },
		1.0f,
		"Neptune",
		*this->textureManager.getTexture("neptune"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::createMars()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {2.279f, 0.0f, 0.0f}, 11 },
		{ {0.0f, 0.0f, 2.407f}, 4 },
		{ 6.39f, 23 },
		{ 3.389f, 6 },
		1.0f,
		"Mars",
		*this->textureManager.getTexture("mars"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp.get());
}

void SpaceSimulationImGui::showFileMenu()
{
}


void SpaceSimulationImGui::showObjectsMenu()
{
	if (ImGui::Selectable("Create colored planet")) {
		createColoredPlanet();
	}

	if (ImGui::Selectable("Create textured planet")) {
		createTexturedPlanet();
	}
	ImGui::Separator();

	if (ImGui::Selectable("Create Solar system")) {
		createSolarSystem();
	}
	ImGui::Separator();

	if (ImGui::BeginMenu("Create real planet")) {
		if (ImGui::Selectable("Create Sun")) {
			createSun();
		}

		if (ImGui::Selectable("Create Mercury")) {
			createMercury();
		}

		if (ImGui::Selectable("Create Venus")) {
			createVenus();
		}

		if (ImGui::Selectable("Create Earth")) {
			createEarth();
		}

		if (ImGui::Selectable("Create Mars")) {
			createMars();
		}

		if (ImGui::Selectable("Create Jupiter")) {
			createJupiter();
		}

		if (ImGui::Selectable("Create Saturn")) {
			createSaturn();
		}

		if (ImGui::Selectable("Create Uranus")) {
			createUranus();
		}

		if (ImGui::Selectable("Create Neptun")) {
			createNeptune();
		}

		ImGui::EndMenu();
	}

	auto& planets = spaceSimulation.getPlanetsRef();
	if (planets.size() > 0) {
		ImGui::Separator();
		if (ImGui::BeginMenu("Delete planets")) {
			showDestroyPlanetsMenu();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit planets")) {
			showEditPlanetsMenu();
			ImGui::EndMenu();
		}
	}
}

void SpaceSimulationImGui::showDestroyPlanetsMenu()
{
	auto& planets = spaceSimulation.getPlanetsRef();
	if (ImGui::ListBoxHeader("Planets to delete"))
	{
		for (int i = 0; i < planets.size(); ++i)
		{
			bool isSelected = std::find(planetsToDelete.begin(), planetsToDelete.end(), i) != planetsToDelete.end();
			if (ImGui::Selectable((std::to_string(i + 1) + ". " + planets[i]->getIdentifier()).c_str(), isSelected))
			{
				if (isSelected)
				{
					planetsToDelete.erase(std::remove(planetsToDelete.begin(), planetsToDelete.end(), i), planetsToDelete.end());
				}
				else
				{
					planetsToDelete.push_back(i);
				}
			}
		}

		ImGui::ListBoxFooter();
	}

	ImGui::SameLine();
	if (ImGui::Button("Delete marked"))
	{
		while (planetsToDelete.size()) {
			auto toDelete = (planets.begin() + *planetsToDelete.rbegin());
			removeObjectFromEdit(toDelete->get());
			spaceSimulation.removePlanetFromSimulation(*toDelete);
			planetsToDelete.pop_back();
		}
	}
	if (ImGui::Button("Delete all"))
	{
		while (planets.size() != 0) {
			spaceSimulation.removePlanetFromSimulation(*planets.rbegin());
		}
		this->objectsToEdit.clear();
	}
}

void SpaceSimulationImGui::showEditPlanetsMenu()
{
	auto& planets = spaceSimulation.getPlanetsRef();

	for (size_t i = 0; i < planets.size(); ++i)
	{
		if (ImGui::Selectable((std::to_string(i + 1) + ". " + planets[i]->getIdentifier()).c_str())) {
			addObjectToEdit(planets[i].get());
		}
	}
}

void SpaceSimulationImGui::showSettingsMenu()
{
	ImGui::Separator();
	if (ImGui::Selectable("Simulation settings")) {
		addObjectToEdit(&spaceSimulation);
	}

	ImGui::Separator();
	if (ImGui::Selectable("First person camera")) {
		auto& camera = spaceSimulation.getCameraManagerRef().getFirstPersonCameraRef();
		addObjectToEdit(&camera);
	}

	if (ImGui::Selectable("Arc ball camera")) {
		auto& camera = spaceSimulation.getCameraManagerRef().getArcBallCameraRef();
		addObjectToEdit(&camera);
	}

	ImGui::Separator();
	if (ImGui::Selectable("Main light")) {
		auto& light = spaceSimulation.getMainLightRef();
		addObjectToEdit(&light);
	}

}
