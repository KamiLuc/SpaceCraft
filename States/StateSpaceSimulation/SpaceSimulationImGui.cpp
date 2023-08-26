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
		2000.0f,
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
		55.0f,
		"Sun",
		*this->textureManager.getTexture("sun"));

	temp->setCanMove(false);
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
		3000.0f,
		"Mercury",
		*this->textureManager.getTexture("mercury"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp);
}

void SpaceSimulationImGui::createVenus()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {1.082f, 0.0f, 0.0f}, 11 },
		{ {0.0f, 0.0f, 3.502f}, 4 },
		{ 4.867f, 24 },
		{ 6.051f, 6 },
		2000.0f,
		"Venus",
		*this->textureManager.getTexture("venus"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp);
}

void SpaceSimulationImGui::createJupiter()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {7.785f, 0.0f, 0.0f}, 11 },
		{ {0.0f, 0.0f, 1.307f}, 4 },
		{ 1.898f, 27 },
		{ 6.699f, 7 },
		500.0f,
		"Jupiter",
		*this->textureManager.getTexture("jupiter"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp);
}

void SpaceSimulationImGui::createSaturn()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {1.427f, 0.0f, 0.0f}, 12 },
		{ {0.0f, 0.0f, 9.672f}, 3 },
		{ 5.683f, 26 },
		{ 5.823f, 7 },
		500.0f,
		"Saturn",
		*this->textureManager.getTexture("saturn"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp);
}

void SpaceSimulationImGui::createUranus()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {2.871f, 0.0f, 0.0f}, 12 },
		{ {0.0f, 0.0f, 6.81f}, 3 },
		{ 8.681f, 25 },
		{ 2.536f, 7 },
		500.0f,
		"Uranus",
		*this->textureManager.getTexture("uranus"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp);
}

void SpaceSimulationImGui::createNeptune()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {4.498f, 0.0f, 0.0f}, 12 },
		{ {0.0f, 0.0f, 5.43f}, 3 },
		{ 1.024f, 26 },
		{ 2.462f, 7 },
		500.0f,
		"Neptune",
		*this->textureManager.getTexture("neptune"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp);
}

void SpaceSimulationImGui::createMars()
{
	auto temp = this->spaceSimulation.createTexturedPlanet(
		{ {2.279f, 0.0f, 0.0f}, 11 },
		{ {0.0f, 0.0f, 2.407f}, 4 },
		{ 6.39f, 23 },
		{ 3.389f, 6 },
		2000.0f,
		"Mars",
		*this->textureManager.getTexture("mars"));

	this->spaceSimulation.addPlanetToSimulation(temp);
	this->addObjectToEdit(temp);
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
			showDeletePlanetsMenu();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit planets")) {
			showEditPlanetsMenu();
			ImGui::EndMenu();
		}

		ImGui::Separator();
		if (ImGui::BeginMenu("Focus planet")) {
			showObjectFocusMenu();
			ImGui::EndMenu();
		}
	}
}

void SpaceSimulationImGui::showDeletePlanetsMenu()
{
	auto& planets = spaceSimulation.getPlanetsRef();
	if (ImGui::ListBoxHeader("Planets to delete"))
	{
		unsigned int index = 0;

		for (auto& planet : planets)
		{
			bool isSelected = std::find(planetsToDelete.begin(), planetsToDelete.end(), index) != planetsToDelete.end();
			if (ImGui::Selectable((std::to_string(index + 1) + ". " + planet->getIdentifier()).c_str(), isSelected))
			{
				if (isSelected)
				{
					planetsToDelete.erase(std::remove(planetsToDelete.begin(), planetsToDelete.end(), index), planetsToDelete.end());
				}
				else
				{
					planetsToDelete.push_back(index);
				}
			}

			++index;
		}

		ImGui::ListBoxFooter();
	}

	if (ImGui::Button("Delete marked"))
	{
		std::sort(planetsToDelete.begin(), planetsToDelete.end());
		while (planetsToDelete.size()) {
			auto toDelete = planets.begin();

			for (unsigned int i = 0; i < *planetsToDelete.rbegin(); ++i) {
				toDelete++;
			}

			removeObjectFromEdit(toDelete->get());
			spaceSimulation.removePlanetFromSimulation(*toDelete);
			planetsToDelete.pop_back();
		}
	}

	if (ImGui::Button("Delete all"))
	{
		while (planets.size() != 0) {
			auto planet = planets.rbegin();
			spaceSimulation.removePlanetFromSimulation(*planet);
		}
		this->objectsToEdit.clear();
	}
}

void SpaceSimulationImGui::showEditPlanetsMenu()
{
	auto& planets = spaceSimulation.getPlanetsRef();
	unsigned int index = 1;

	for (const auto& planet : planets)
	{
		if (ImGui::Selectable((std::to_string(index) + ". " + planet->getIdentifier()).c_str())) {
			addObjectToEdit(planet.get());
		}
		++index;
	}
}

void SpaceSimulationImGui::showObjectFocusMenu()
{
	auto& planets = spaceSimulation.getPlanetsRef();
	unsigned int index = 1;

	for (const auto& planet : planets)
	{
		if (ImGui::Selectable((std::to_string(index) + ". " + planet->getIdentifier()).c_str())) {
			this->spaceSimulation.focusPlanet(planet);
		}
		++index;
	}
}

void SpaceSimulationImGui::deleteObject(std::shared_ptr<EditableViaImGui> object)
{
	deleteObject(object.get());
}

void SpaceSimulationImGui::deleteObject(EditableViaImGui* object)
{
	auto& planets = spaceSimulation.getPlanetsRef();
	auto planet = std::find_if(planets.begin(), planets.end(), [&object](std::shared_ptr<RenderablePlanet> obj) {
		return object == obj.get(); });

	if (planet != planets.end()) {
		removeObjectFromEdit(object);
		spaceSimulation.removePlanetFromSimulation(*planet);
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
