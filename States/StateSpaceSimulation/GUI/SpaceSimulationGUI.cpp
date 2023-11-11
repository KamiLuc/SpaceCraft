#include "SpaceSimulationGUI.h"


SpaceSimulationGUI::SpaceSimulationGUI(SpaceSimulationSettings& spaceSimulationSettings, PlanetCreator& planetCreator,
									   Serializer& serializer, SceneContext& sceneContext)
	: spaceSimulationSettings(spaceSimulationSettings)
	, planetDistanceVisualizer(planetCreator.getPlanetContainerRef())
	, planetCreator(planetCreator)
	, sceneContext(sceneContext)
	, serializer(serializer)
	, spaceSimulationSettingsObjectEditor("Edit simulation settings", { 550, 153 }, { 550, 153 })
	, mainLightObjectEditor("Edit main light", { 320, 79 }, { 320, 79 })
	, planetDistanceVisualizerEditor("Distance visualizer", { 500, 230 }, { 1000, 1000 })
{
	spaceSimulationSettings.registerEditor(&spaceSimulationSettingsObjectEditor);
	sceneContext.mainLight->registerEditor(&mainLightObjectEditor);
	planetDistanceVisualizer.registerEditor(&planetDistanceVisualizerEditor);
}

void SpaceSimulationGUI::draw()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			showFileMenu();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Settings"))
		{
			showSettingsMenu();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Objects"))
		{
			showObjectsMenu();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools"))
		{
			showToolsMenu();
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	drawEditors();
}

void SpaceSimulationGUI::drawEditors()
{
	planetCreator.drawEditors();
	spaceSimulationSettingsObjectEditor.draw();
	sceneContext.cameraManager->drawEditors();
	mainLightObjectEditor.draw();
	planetDistanceVisualizerEditor.draw();
}

void SpaceSimulationGUI::createColoredPlanet()
{
	auto temp = planetCreator.buildColoredPlanet(
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 11), PhysicalUnit(0.0f, 11), PhysicalUnit(0.0f, 11)}),
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4)}),
		{ 0.0f, 0 },
		{ 5.0f, 10 },
		1.0f,
		"Planet",
		{ 0.3f, 0.2f, 0.8f, 1.0f });
	temp->startEditing();
}

void SpaceSimulationGUI::createTexturedPlanet()
{
	auto temp = planetCreator.buildTexturedPlanet(
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 11), PhysicalUnit(0.0f, 11), PhysicalUnit(0.0f, 11)}),
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4)}),
		{ 0.0f, 0 },
		{ 5.0f, 10 },
		1.0f,
		"Planet",
		planetCreator.getTextureManager()->getTexture(planetCreator.getTextureManager()->getTexturesNames()[0]));
	temp->startEditing();
}

void SpaceSimulationGUI::createTexturedStar()
{
	auto temp = planetCreator.buildTexturedStar(
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 11), PhysicalUnit(0.0f, 11), PhysicalUnit(0.0f, 11)}),
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4)}),
		{ 0.0f, 0 },
		{ 5.0f, 10 },
		1.0f,
		"Star",
		"sun");
	temp->startEditing();
}

void SpaceSimulationGUI::createSolarSystem()
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
}

void SpaceSimulationGUI::createEarth()
{
	auto temp = planetCreator.buildTexturedPlanet(
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(1.496f, 11), PhysicalUnit(0.0f, 11), PhysicalUnit(0.0f, 11)}),
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4), PhysicalUnit(2.978f, 4)}),
		{ 5.972f, 24 },
		{ 6.371f, 6 },
		2000.0f,
		"Earth",
		"earth");
}

void SpaceSimulationGUI::createSun()
{
	auto temp = planetCreator.buildTexturedStar(
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 11), PhysicalUnit(0.0f, 11), PhysicalUnit(0.0f, 11)}),
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4)}),
		{ 1.989f, 30 },
		{ 6.963f, 8 },
		55.0f,
		"Sun",
		"sun");
}

void SpaceSimulationGUI::createMercury()
{
	auto temp = planetCreator.buildTexturedPlanet(
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(5.79f, 10), PhysicalUnit(0.0f, 10), PhysicalUnit(0.0f, 10)}),
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4), PhysicalUnit(4.787f, 4)}),
		{ 3.301f, 23 },
		{ 2.439f, 6 },
		3000.0f,
		"Mercury",
		"mercury");
}

void SpaceSimulationGUI::createVenus()
{
	auto temp = planetCreator.buildTexturedPlanet(
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(1.082f, 11), PhysicalUnit(0.0f, 11), PhysicalUnit(0.0f, 11)}),
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4), PhysicalUnit(3.502f, 4)}),
		{ 4.867f, 24 },
		{ 6.051f, 6 },
		2000.0f,
		"Venus",
		"venus");
}

void SpaceSimulationGUI::createJupiter()
{
	auto temp = planetCreator.buildTexturedPlanet(
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(7.785f, 11), PhysicalUnit(0.0f, 11), PhysicalUnit(0.0f, 11)}),
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4), PhysicalUnit(1.307f, 4)}),
		{ 1.898f, 27 },
		{ 6.699f, 7 },
		500.0f,
		"Jupiter",
		"jupiter");
}

void SpaceSimulationGUI::createSaturn()
{
	auto temp = planetCreator.buildTexturedPlanet(
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(1.427f, 12), PhysicalUnit(0.0f, 12), PhysicalUnit(0.0f, 12)}),
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 3), PhysicalUnit(0.0f, 3), PhysicalUnit(9.672f, 3)}),
		{ 5.683f, 26 },
		{ 5.823f, 7 },
		500.0f,
		"Saturn",
		"saturn");
}

void SpaceSimulationGUI::createUranus()
{
	auto temp = planetCreator.buildTexturedPlanet(
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(2.871f, 12), PhysicalUnit(0.0f, 12), PhysicalUnit(0.0f, 12)}),
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 3), PhysicalUnit(0.0f, 3), PhysicalUnit(6.81f, 3)}),
		{ 8.681f, 25 },
		{ 2.536f, 7 },
		3000.0f,
		"Uranus",
		"uranus");
}

void SpaceSimulationGUI::createNeptune()
{
	auto temp = planetCreator.buildTexturedPlanet(
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(4.498f, 12), PhysicalUnit(0.0f, 12), PhysicalUnit(0.0f, 12)}),
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 3), PhysicalUnit(0.0f, 3), PhysicalUnit(5.43f, 3)}),
		{ 1.024f, 26 },
		{ 2.462f, 7 },
		5000.0f,
		"Neptune",
		"neptune");
}

void SpaceSimulationGUI::createMars()
{
	auto temp = planetCreator.buildTexturedPlanet(
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(2.279f, 11), PhysicalUnit(0.0f, 11), PhysicalUnit(0.0f, 11)}),
		PhysicalUnitVec<3>(std::array<PhysicalUnit, 3>{PhysicalUnit(0.0f, 4), PhysicalUnit(0.0f, 4), PhysicalUnit(2.407f, 4)}),
		{ 6.39f, 23 },
		{ 3.389f, 6 },
		2000.0f,
		"Mars",
		"mArS");
}

void SpaceSimulationGUI::loadSavedSimulations()
{
	savedSimulations.clear();
	auto savedSimulationsDirectory = serializer.getSaveDirectiory();

	for (const auto& dirEntry : std::filesystem::directory_iterator { savedSimulationsDirectory })
	{
		if (dirEntry.is_regular_file() && dirEntry.path().extension().string() == ".sc")
		{
			savedSimulations.emplace_back(dirEntry.path());
		}
	}
}

void SpaceSimulationGUI::showFileMenu()
{
	if (ImGui::Button("Save", ImVec2(70, 30)))
	{
		ImGui::OpenPopup("Save simulation");
		spaceSimulationSettings.pauseSimulation = true;
		spaceSimulationSettings.disableEvents();
	}
	showSaveSimulationModal("Save simulation");

	if (ImGui::Button("Load", ImVec2(70, 30)))
	{
		loadSavedSimulations();
		ImGui::OpenPopup("Load simulation");
	}
	showLoadSimulationModal("Load simulation");
}

void SpaceSimulationGUI::showObjectsMenu()
{
	if (ImGui::Selectable("Create colored planet"))
	{
		createColoredPlanet();
	}

	if (ImGui::Selectable("Create textured planet"))
	{
		createTexturedPlanet();
	}

	if (ImGui::Selectable("Create star"))
	{
		createTexturedStar();
	}

	ImGui::Separator();
	if (ImGui::Selectable("Create Solar system"))
	{
		createSolarSystem();
	}

	ImGui::Separator();
	if (ImGui::BeginMenu("Create real planet"))
	{
		if (ImGui::Selectable("Create Sun"))
		{
			createSun();
		}

		if (ImGui::Selectable("Create Mercury"))
		{
			createMercury();
		}

		if (ImGui::Selectable("Create Venus"))
		{
			createVenus();
		}

		if (ImGui::Selectable("Create Earth"))
		{
			createEarth();
		}

		if (ImGui::Selectable("Create Mars"))
		{
			createMars();
		}

		if (ImGui::Selectable("Create Jupiter"))
		{
			createJupiter();
		}

		if (ImGui::Selectable("Create Saturn"))
		{
			createSaturn();
		}

		if (ImGui::Selectable("Create Uranus"))
		{
			createUranus();
		}

		if (ImGui::Selectable("Create Neptun"))
		{
			createNeptune();
		}

		ImGui::EndMenu();
	}

	auto& planets = planetCreator.getPlanetContainerRef();
	if (planets.size() > 0)
	{
		ImGui::Separator();
		if (ImGui::BeginMenu("Delete planets"))
		{
			showDeletePlanetsMenu();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Edit planets"))
		{
			showEditPlanetsMenu();
			ImGui::EndMenu();
		}

		ImGui::Separator();
		if (ImGui::BeginMenu("Focus planet"))
		{
			showObjectFocusMenu();
			ImGui::EndMenu();
		}
	}
}

void SpaceSimulationGUI::showToolsMenu()
{
	if (ImGui::Selectable("Distance visualizer"))
	{
		planetDistanceVisualizer.startEditing();
	}
}

void SpaceSimulationGUI::showDeletePlanetsMenu()
{
	auto& planets = planetCreator.getPlanetContainerRef();
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
		while (planetsToDelete.size())
		{
			auto toDelete = planets.begin();
			for (unsigned int i = 0; i < *planetsToDelete.rbegin(); ++i)
			{
				++toDelete;
			}

			planetCreator.removePlanetFromSimulation(toDelete->get());
			planetsToDelete.pop_back();
		}
	}

	if (ImGui::Button("Delete all"))
	{
		planetCreator.clearObjects();
	}
}

void SpaceSimulationGUI::showEditPlanetsMenu()
{
	auto& planets = planetCreator.getPlanetContainerRef();
	unsigned int index = 1;

	for (const auto& planet : planets)
	{
		if (ImGui::Selectable((std::to_string(index) + ". " + planet->getIdentifier()).c_str()))
		{
			planet->startEditing();
		}
		++index;
	}
}

void SpaceSimulationGUI::showObjectFocusMenu()
{
	auto& planets = planetCreator.getPlanetContainerRef();
	unsigned int index = 1;

	for (const auto& planet : planets)
	{
		if (ImGui::Selectable((std::to_string(index) + ". " + planet->getIdentifier()).c_str()))
		{
			spaceSimulationSettings.focusedPlanet = planet;
		}
		++index;
	}
}

void SpaceSimulationGUI::showSaveSimulationModal(const std::string & modal)
{
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	ImGui::SetNextWindowSize(ImVec2(250, 80));
	if (ImGui::BeginPopupModal(modal.c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize))
	{
		static char inputText[256] = "";

		ImGui::InputText("File name", inputText, sizeof(inputText));

		if (ImGui::Button("Save", ImVec2(120, 0)))
		{
			std::string fileName { inputText };
			if (fileName.empty())
			{
				boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
				fileName = to_simple_string(now);

				std::for_each(fileName.begin(), fileName.end(), [](auto &el)
							  {
								  if (el == ':')
								  {
									  el = '-';
								  }
							  });
			}

			auto& planets = planetCreator.getPlanetContainerRef();
			serializer.serializeObjects(serializer.getSaveDirectiory() / fileName.append(".sc"), planets.begin(), planets.end());
			memset(inputText, 0, 256);
			spaceSimulationSettings.enableEvents();
			ImGui::CloseCurrentPopup();
		}

		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();

		if (ImGui::Button("Cancel", ImVec2(120, 0)))
		{
			memset(inputText, 0, 256);
			spaceSimulationSettings.enableEvents();
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void SpaceSimulationGUI::showLoadSimulationModal(const std::string & modal)
{
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	ImGui::SetNextWindowSize(ImVec2(300, 300));
	if (ImGui::BeginPopupModal(modal.c_str(), nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoResize))
	{
		int selectedId = -1;

		ImVec2 tableSize(300, 197);
		if (ImGui::BeginChild("SimulationsTable", tableSize, false, ImGuiWindowFlags_HorizontalScrollbar))
		{
			for (int i = 0; i < savedSimulations.size(); ++i)
			{
				bool isSelected = (i == selectedId);

				if (ImGui::Selectable(savedSimulations[i].stem().string().c_str(), isSelected))
				{
					if (isSelected)
					{
						selectedId = -1;
					}
					else
					{
						selectedId = i;
					}

					spaceSimulationSettings.pauseSimulation = true;
					planetCreator.clearObjects();
					serializer.createSerializedObjects(savedSimulations[selectedId]);
				}
			}

			ImGui::EndChild();
		}

		ImGui::Separator();
		ImGui::SetCursorPosX((ImGui::GetWindowWidth() - 120) * 0.5f);
		ImGui::SetCursorPosY((ImGui::GetWindowHeight() - ImGui::GetFrameHeightWithSpacing()) * 0.9f);
		if (ImGui::Button("Cancel", ImVec2(120, 30)))
		{
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

//void SpaceSimulationGUI::deleteObject(std::shared_ptr<EditableViaImGui> object)
//{
//	deleteObject(object.get());
//}
//
//void SpaceSimulationGUI::deleteObject(EditableViaImGui *object)
//{
//	auto& planets = spaceSimulation.planets;
//	auto planet = std::find_if(planets.begin(), planets.end(), [&object](std::shared_ptr<RenderablePlanet> obj)
//							   {
//								   return object == obj.get();
//							   });
//
//	if (planet != planets.end())
//	{
//		removeObjectFromEdit(object);
//		spaceSimulation.removePlanetFromSimulation(*planet);
//	}
//}

void SpaceSimulationGUI::showSettingsMenu()
{
	if (ImGui::Selectable("Simulation settings"))
	{
		spaceSimulationSettings.startEditing();
	}

	ImGui::Separator();
	if (ImGui::Selectable("First person camera"))
	{
		sceneContext.cameraManager->getFirstPersonCameraRef().startEditing();
	}

	if (ImGui::Selectable("Arc ball camera"))
	{
		sceneContext.cameraManager->getArcBallCameraRef().startEditing();
	}

	ImGui::Separator();
	if (ImGui::Selectable("Main light"))
	{
		sceneContext.mainLight->startEditing();
	}
}
