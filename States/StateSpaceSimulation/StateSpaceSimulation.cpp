#include "StateSpaceSimulation.h"

StateSpaceSimulation::StateSpaceSimulation(StateManager* stateManager, Render render)
	: BaseState(stateManager, render)
	, gravitationalConstant(6.67430f, -11)
{
}

void StateSpaceSimulation::onCreate()
{
	auto& textureManager = stateManager->getContext()->textureManager;
	auto& shaderManager = stateManager->getContext()->shaderManager;
	auto& eventManager = stateManager->getContext()->eventManager;
	auto& window = stateManager->getContext()->window;
	auto& settings = Settings::GlobalSettings::getInstance();

	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::Black);

	auto cameraManager = std::make_shared<CameraManagerToSFMLFrameworkAdapter>(settings.arcBallCameraSettings,
																			   settings.firstPesonCameraSettings, window->getRenderWindow());
	auto mainLight = std::make_shared<OmnipresentLight>(settings.mainLightSettings.color, settings.mainLightSettings.ambientIntensity);
	sceneContext = SceneContext(cameraManager, shaderManager, mainLight);

	planetCreator = std::make_unique<PlanetCreator>(textureManager, sceneContext.pointLights);
	skybox = std::make_unique<Skybox>(textureManager->getSkyboxTexture());
	coordinateSystemAxes = std::make_unique<CoordinateSystemAxes>(glm::vec3(0.0f, 0.0f, 0.0f));

	serializer.setSaveDirectiory(settings.savedSimulationsPath);
	serializer.registerObjectCreator(SerializableObjectId::COLORED_PLANET,
									 [&](auto& data) { planetCreator->createColoredPlanetFromArchive(data); });
	serializer.registerObjectCreator(SerializableObjectId::TEXTURED_PLANET,
									 [&](auto& data) { planetCreator->createTexturedPlanetFromArchive(data); });
	serializer.registerObjectCreator(SerializableObjectId::TEXTURED_STAR,
									 [&](auto& data) { planetCreator->createTexturedStarFromArchive(data); });

	simulationSettings = SpaceSimulationSettings(true, false, coordinateSystemAxes->getLineWidthPtr(), { 8.64f, 4 }, eventManager);
	simulationGui = std::make_unique<SpaceSimulationGUI>(simulationSettings, *planetCreator, serializer, sceneContext);

	addCallbacks();
}

void StateSpaceSimulation::onDestroy()
{
	removeCallbacks();
}

void StateSpaceSimulation::update(const sf::Time& time)
{
	auto realTimeInSec = static_cast<float>(time.asSeconds());
	sceneContext.cameraManager->updateCameraPosition(realTimeInSec);
	sceneContext.lastUpdateInSec = realTimeInSec;
	sceneContext.lifeTimeInSec += realTimeInSec;

	auto& planets = planetCreator->getPlanetContainerRef();
	float simTime = realTimeInSec * static_cast<float>(simulationSettings.simulationSpeed.getValue());

	if (!simulationSettings.pauseSimulation && !planets.empty())
	{
		unsigned int toDrop = 1;
		for (const auto& firstPlanet : planets)
		{
			for (const auto& secondPlanet : planets | std::views::drop(toDrop++))
			{
				auto distanceVec = secondPlanet->getPosition() - firstPlanet->getPosition();
				auto distanceSquared = distanceVec.getLength().getSquared();
				auto force = gravitationalConstant * (firstPlanet->getMass() * secondPlanet->getMass()) / distanceSquared;
				auto forceVec = distanceVec.getNormalized() * force;

				auto firstAcceleration = forceVec / firstPlanet->getMass();
				auto secondAcceleration = (forceVec * (-1)) / secondPlanet->getMass();

				firstPlanet->setVelocity(firstPlanet->getVelocity() + firstAcceleration * simTime);
				secondPlanet->setVelocity(secondPlanet->getVelocity() + secondAcceleration * simTime);
			}
		}

		for (auto& el : planets)
		{
			el->update(simTime, realTimeInSec);
		}
	}

	if (simulationSettings.focusedPlanet != nullptr)
	{
		sceneContext.cameraManager->observePoint(simulationSettings.focusedPlanet->getPositionInWorldSpace());
	}
	else
	{
		sceneContext.cameraManager->observePoint({ 0.0f, 0.0f, 0.0f });
	}
}

void StateSpaceSimulation::draw()
{
	skybox->render(sceneContext);
	simulationGui->draw();

	for (const auto& el : planetCreator->getRenderContainerRef())
	{
		renderObject(*el);
	}

	if (simulationSettings.renderCoordinateAxes)
	{
		renderObject(*coordinateSystemAxes);
	}

	sceneContext.shaderManager->setLastUsedShader(nullptr);
	stateManager->getContext()->window->renderImGui();
}

void StateSpaceSimulation::focusPlanet(std::shared_ptr<RenderablePlanet> planet)
{
	auto planetInWorldPos = planet->getPositionInWorldSpace();
	auto newCameraPosComponent = planet->getRadiusInWorldSpace() * -11.0f;
	auto newCameraPos = planetInWorldPos - glm::vec3(newCameraPosComponent);

	simulationSettings.focusedPlanet = planet;
	sceneContext.cameraManager->getArcBallCameraRef().setCameraPosition(newCameraPos);
}

void StateSpaceSimulation::renderObject(const Renderable& renderable)
{
	renderable.render(sceneContext);
}

void StateSpaceSimulation::focusCenter(EventDetails* details)
{
	simulationSettings.focusedPlanet = nullptr;
	sceneContext.cameraManager->observePoint({ 0.0f, 0.0f, 0.0f });
}

void StateSpaceSimulation::switchSimulationState(EventDetails* e)
{
	simulationSettings.pauseSimulation = !simulationSettings.pauseSimulation;
}

void StateSpaceSimulation::mouseLeftClick(EventDetails* details)
{
	handleMouse(details, Mouse::LEFT);
}

void StateSpaceSimulation::mouseRightClick(EventDetails* details)
{
	handleMouse(details, Mouse::RIGHT);
}

void StateSpaceSimulation::handleMouse(EventDetails* details, Mouse mouseButton)
{
	if (!ImGui::GetIO().WantCaptureMouse)
	{
		float x = static_cast<float>(details->mouse.x);
		float y = static_cast<float>(details->mouse.y);
		float z = 0.5f;
		auto winSize = stateManager->getContext()->window->getRenderWindow()->getSize();
		auto currentCamera = sceneContext.cameraManager->getCurrentCamera();
		glm::vec4 viewPort { 0.0f, 0.0f, winSize.x, winSize.y };
		glm::mat4 projectionMatrix = currentCamera->getProjectionMatrix();
		glm::mat4 viewMatrix = currentCamera->getViewMatrix();

		glm::vec3 nearPlane = glm::unProject(glm::vec3(x, winSize.y - y, 0.0f), viewMatrix, projectionMatrix, viewPort);
		glm::vec3 farPlane = glm::unProject(glm::vec3(x, winSize.y - y, 0.99f), viewMatrix, projectionMatrix, viewPort);
		glm::vec3 rayDirection = glm::normalize(farPlane - nearPlane);

		for (const auto& planet : planetCreator->getPlanetContainerRef())
		{
			glm::vec3 objectToClick = planet->getPositionInWorldSpace() - nearPlane;
			float intersectionDistance = glm::dot(objectToClick, rayDirection);
			glm::vec3 intersectionPoint = nearPlane + (rayDirection * intersectionDistance);
			float distanceToIntersection = glm::distance(planet->getPositionInWorldSpace(), intersectionPoint);

			auto r = planet->getRadiusInWorldSpace();

			if (distanceToIntersection < planet->getRadiusInWorldSpace())
			{
				if (mouseButton == Mouse::LEFT)
				{
					planet->startEditing();
				}
				else if (mouseButton == Mouse::RIGHT)
				{
					focusPlanet(planet);
				}
				break;
			}
		}
	}
}

void StateSpaceSimulation::addCallbacks()
{
	auto eventManager = stateManager->getContext()->eventManager;
	auto cameraManager = sceneContext.cameraManager;

	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Start_Camera_Forward", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Stop_Camera_Forward", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Start_Camera_Backward", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Stop_Camera_Backward", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Start_Camera_Left", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Stop_Camera_Left", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Start_Camera_Right", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Stop_Camera_Right", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Enable_Mouse_Camera_Move", &CameraManagerToSFMLFrameworkAdapter::enableMouseCameraMove, cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Disable_Mouse_Camera_Move", &CameraManagerToSFMLFrameworkAdapter::disableMouseCameraMove, cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Change_Camera", &CameraManagerToSFMLFrameworkAdapter::changeCamera, cameraManager.get());
	eventManager->addCallback<StateSpaceSimulation>(StateType::SpaceSimulation, "Pause_Simulation", &StateSpaceSimulation::switchSimulationState, this);
	eventManager->addCallback<StateSpaceSimulation>(StateType::SpaceSimulation, "Mouse_Left_Click", &StateSpaceSimulation::mouseLeftClick, this);
	eventManager->addCallback<StateSpaceSimulation>(StateType::SpaceSimulation, "Mouse_Right_Click", &StateSpaceSimulation::mouseRightClick, this);
	eventManager->addCallback<StateSpaceSimulation>(StateType::SpaceSimulation, "Focus_Center", &StateSpaceSimulation::focusCenter, this);
}

void StateSpaceSimulation::removeCallbacks()
{
	auto eventManager = stateManager->getContext()->eventManager;

	eventManager->removeCallback(StateType::SpaceSimulation, "Start_Camera_Forward");
	eventManager->removeCallback(StateType::SpaceSimulation, "Stop_Camera_Forward");
	eventManager->removeCallback(StateType::SpaceSimulation, "Start_Camera_Backward");
	eventManager->removeCallback(StateType::SpaceSimulation, "Stop_Camera_Backward");
	eventManager->removeCallback(StateType::SpaceSimulation, "Start_Camera_Left");
	eventManager->removeCallback(StateType::SpaceSimulation, "Stop_Camera_Left");
	eventManager->removeCallback(StateType::SpaceSimulation, "Start_Camera_Right");
	eventManager->removeCallback(StateType::SpaceSimulation, "Stop_Camera_Right");
	eventManager->removeCallback(StateType::SpaceSimulation, "Enable_Mouse_Camera_Move");
	eventManager->removeCallback(StateType::SpaceSimulation, "Disable_Mouse_Camera_Move");
	eventManager->removeCallback(StateType::SpaceSimulation, "Change_Camera");
	eventManager->removeCallback(StateType::SpaceSimulation, "Pause_Simulation");
	eventManager->removeCallback(StateType::SpaceSimulation, "Mouse_Left_Click");
	eventManager->removeCallback(StateType::SpaceSimulation, "Mouse_Left_Right");
	eventManager->removeCallback(StateType::SpaceSimulation, "Focus_Center");
}

void StateSpaceSimulation::activate()
{
}

void StateSpaceSimulation::deactivate()
{
}
