#include "StateSpaceSimulation.h"

StateSpaceSimulation::StateSpaceSimulation(StateManager* stateManager, Render render)
	: BaseState(stateManager, render)
	, simulationSpeed(8.64f, 4)
	, gravitationalConstant(6.67430f, -11)
	, pauseSimulation(true)
	, renderCoordinateAxes(true)
	, shaderManager(nullptr)
	, textureManager(nullptr)
{
}

void StateSpaceSimulation::onCreate()
{
	this->shaderManager = stateManager->getContext()->shaderManager;
	this->textureManager = stateManager->getContext()->textureManager;

	coordinateSystemAxes = std::make_unique<CoordinateSystemAxes>(shaderManager, glm::vec3(0.0f, 0.0f, 0.0f));

	auto window = stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::Black);

	auto& settings = Settings::GlobalSettings::getInstance();

	auto cameraManager = std::make_shared<CameraManagerToSFMLFrameworkAdapter>(settings.getArcBallCameraSettings(),
		settings.getFirstPersonCameraSettings(), window->getRenderWindow());
	auto mainLight = std::make_shared<Light>(settings.getMainLightSettings());

	simulationGui = std::make_unique<SpaceSimulationImGui>(*this, *textureManager);

	shinyMaterial = std::make_unique<Material>(2.0f, 1024.0f);
	dullMaterial = std::make_shared<Material>(0.3f, 4.0f);

	sceneContext = std::make_shared<SceneContext>(cameraManager, mainLight, dullMaterial);

	addCallbacks();
}

void StateSpaceSimulation::onDestroy()
{
	removeCallbacks();
}

void StateSpaceSimulation::activate()
{
}

void StateSpaceSimulation::deactivate()
{
}

void StateSpaceSimulation::update(const sf::Time& time)
{
	auto realTimeInSec = static_cast<float>(time.asSeconds());
	sceneContext->cameraManager->updateCameraPosition(realTimeInSec);

	float simTime = realTimeInSec * static_cast<float>(this->simulationSpeed.getValue());
	
	if (!pauseSimulation && !planets.empty()) {

		unsigned int toDrop = 1;
		for (const auto& firstPlanet : planets) {

			for (const auto& secondPlanet : planets | std::views::drop(toDrop++)) {

				auto distanceVec = secondPlanet->getPosition() - firstPlanet->getPosition();
				auto distanceSquared = distanceVec.getLength().getSquared();
				auto force = gravitationalConstant * (firstPlanet->getMass() * secondPlanet->getMass()) / distanceSquared;
				auto forceVec = distanceVec.getNormalized() *  force;

				auto firstAcceleration = forceVec / firstPlanet->getMass();
				auto secondAcceleration = (forceVec * (-1)) / secondPlanet->getMass();

				firstPlanet->setVelocity(firstPlanet->getVelocity() + firstAcceleration * simTime);
				secondPlanet->setVelocity(secondPlanet->getVelocity() + secondAcceleration * simTime);
			}
		}

		for (auto& el : planets) {
			el->update(simTime, realTimeInSec);
		}
	}
	
	if (focusedPlanet != nullptr) {
		sceneContext->cameraManager->observePoint(focusedPlanet->getPositionInWorldSpace());
	}
	else {
		sceneContext->cameraManager->observePoint({ 0.0f, 0.0f, 0.0f });
	}
}

void StateSpaceSimulation::draw()
{
	simulationGui->draw();

	for (const auto& el : objectsToRender) {
		renderObject(*el);
	}

	if (renderCoordinateAxes) {
		renderObject(*coordinateSystemAxes);
	}

	shaderManager->setLastUsedShader(nullptr);
	stateManager->getContext()->window->renderImGui();
}

std::shared_ptr<TexturedPlanet> StateSpaceSimulation::createTexturedPlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
	const PhysicalUnit& radius, float scale, const std::string& identifier, const Texture& texture)
{
	return std::make_shared<TexturedPlanet>(position, velocity, mass, radius, scale, identifier, shaderManager, texture);
}

std::shared_ptr<ColoredPlanet> StateSpaceSimulation::createColoredPlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
	const PhysicalUnit& radius, float scale, const std::string& identifier, const glm::vec4& color)
{
	return std::make_shared<ColoredPlanet>(position, velocity, mass, radius, scale, identifier, shaderManager, color);
}

std::list<std::shared_ptr<RenderablePlanet>>& StateSpaceSimulation::getPlanetsRef()
{
	return planets;
}

Light& StateSpaceSimulation::getMainLightRef()
{
	return *sceneContext->mainLight;
}

CameraManager& StateSpaceSimulation::getCameraManagerRef()
{
	return *sceneContext->cameraManager;
}

PhysicalUnit& StateSpaceSimulation::getSimulationSpeedRef()
{
	return simulationSpeed;
}

void StateSpaceSimulation::addPlanetToSimulation(std::shared_ptr<RenderablePlanet> planet)
{
	planets.push_back(planet);
	addObjectToRender(planet);
}

void StateSpaceSimulation::removePlanetFromSimulation(std::shared_ptr<RenderablePlanet> planet)
{
	planets.remove(planet);
	removeObjectToRender(planet);
}

void StateSpaceSimulation::addObjectToRender(std::shared_ptr<Renderable> object)
{
	objectsToRender.push_back(object);
}

void StateSpaceSimulation::removeObjectToRender(std::shared_ptr<Renderable> object)
{
	objectsToRender.remove(object);
}

void StateSpaceSimulation::focusPlanet(std::shared_ptr<RenderablePlanet> planet)
{
	auto planetInWorldPos = planet->getPositionInWorldSpace();
	auto newCameraPosComponent = planet->getRadiusInWorldSpace() * -11.0f;
	auto newCameraPos = planetInWorldPos - glm::vec3(newCameraPosComponent);

	this->focusedPlanet = planet;
	getCameraManagerRef().getArcBallCameraRef().setCameraPosition(newCameraPos);
}

void StateSpaceSimulation::editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui)
{
	if (beginImGui) {
		ImGui::Begin(("Simulation settings " + std::to_string(windowID)).c_str());
	}
	else {
		ImGui::Separator();
	}

	ImGui::Checkbox("Render coordinate system axis", &renderCoordinateAxes);
	ImGui::DragFloat("Axis line width", coordinateSystemAxes->getLineWidthPtr(), 0.1f, 1.0f, 30.0f);

	ImGui::Separator();
	ImGui::Checkbox("Pause simulation", &pauseSimulation);
	ImGui::InputFloat("Simulation speed", simulationSpeed.getBasePtr());
	ImGui::InputInt("Simulation speed exponent", simulationSpeed.getExponentPtr());

	ImGui::Separator();
	if (ImGui::Button("Close", { ImGui::GetWindowWidth(), 20 })) {
		objectHandler.removeObjectFromEdit(this);
	}

	if (beginImGui) {
		ImGui::End();
	}
}

void StateSpaceSimulation::renderObject(const Renderable& renderable)
{
	renderable.render(sceneContext);
}

void StateSpaceSimulation::focusCenter(EventDetails* details)
{
	focusedPlanet = nullptr;
	sceneContext->cameraManager->observePoint({ 0.0f, 0.0f, 0.0f });
}

void StateSpaceSimulation::switchSimulationState(EventDetails* e)
{
	pauseSimulation = !pauseSimulation;
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
	if (!ImGui::GetIO().WantCaptureMouse) {
		float x = static_cast<float>(details->mouse.x);
		float y = static_cast<float>(details->mouse.y);
		float z = 0.5f;
		auto winSize = stateManager->getContext()->window->getRenderWindow()->getSize();
		glm::vec4 viewPort{ 0.0f, 0.0f, winSize.x, winSize.y };
		glm::mat4 projectionMatrix = sceneContext->cameraManager->getProjectionMatrix();
		glm::mat4 viewMatrix = sceneContext->cameraManager->getViewMatrix();

		glm::vec3 nearPlane = glm::unProject(glm::vec3(x, winSize.y - y, 0.0f), viewMatrix, projectionMatrix, viewPort);
		glm::vec3 farPlane = glm::unProject(glm::vec3(x, winSize.y - y, 0.99f), viewMatrix, projectionMatrix, viewPort);
		glm::vec3 rayDirection = glm::normalize(farPlane - nearPlane);

		for (const auto& planet : planets) {

			glm::vec3 objectToClick = planet->getPositionInWorldSpace() - nearPlane;

			float intersectionDistance = glm::dot(objectToClick, rayDirection);
			glm::vec3 intersectionPoint = nearPlane + (rayDirection * intersectionDistance);
			float distanceToIntersection = glm::distance(planet->getPositionInWorldSpace(), intersectionPoint);

			auto r = planet->getRadiusInWorldSpace();

			if (distanceToIntersection < planet->getRadiusInWorldSpace()) {

				if (mouseButton == Mouse::LEFT) {
					simulationGui->addObjectToEdit(planet);
				}
				else if (mouseButton == Mouse::RIGHT) {
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
	auto cameraManager = sceneContext->cameraManager;

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
