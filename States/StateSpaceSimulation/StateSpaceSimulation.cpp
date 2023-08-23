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

	coordinateSystemAxes = std::make_unique<CoordinateSystemAxes>(shaderManager, Measure<3>({ 0.0f, 0.0f, 0.0f }));

	auto window = stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::Black);

	auto& settings = Settings::GlobalSettings::getInstance();

	auto cameraManager = std::make_shared<CameraManagerToSFMLFrameworkAdapter>(settings.getArcBallCameraSettings(),
		settings.getFirstPersonCameraSettings(), window->getRenderWindow());
	auto mainLight = std::make_shared<Light>(settings.getMainLightSettings());

	simulationGui = std::make_unique<SpaceSimulationImGui>(*this, *textureManager);

	shinyMaterial = std::make_unique<Material>(2.0f, 1024.0f);
	dullMaterial = std::make_unique<Material>(0.3f, 4.0f);

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
	auto timeInSec = static_cast<float>(time.asSeconds());
	sceneContext->cameraManager->updateCameraPosition(timeInSec);

	float simTime = timeInSec * static_cast<float>(this->simulationSpeed.getGlmVec()[0]);

	if (!pauseSimulation) {
		auto it = planets.begin();
		for (; it != planets.end()--; ++it) {

			std::list<std::shared_ptr<RenderablePlanet>>::iterator it2 = it;
			it2++;

			for (; it2 != planets.end(); ++it2) {

				auto& planet = *it;
				auto& otherPlanet = *it2;

				glm::vec3 direction = otherPlanet->getPosition() - planet->getPosition();
				float distance = glm::length(direction);

				auto t1 = planet->getMass() * gravitationalConstant * otherPlanet->getMass();
				auto t2 = distance * distance;

				glm::vec1 gravityForce = t1 / t2;
				glm::vec3 force = gravityForce * glm::normalize(direction);

				glm::vec3 acceleration = force / planet->getMass().getGlmVec();
				glm::vec3 otherAcceleration = -force / otherPlanet->getMass().getGlmVec();

				planet->setVelocity(planet->getVelocity() + acceleration * simTime);
				otherPlanet->setVelocity(otherPlanet->getVelocity() + otherAcceleration * simTime);
			}
		}

		for (auto& el : planets) {
			el->update(simTime);
		}
	}

	if (focusedPlanet != nullptr) {
		sceneContext->cameraManager->observePoint(focusedPlanet->getPositionInWorldSpace().getGlmVec());
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

std::shared_ptr<TexturedPlanet> StateSpaceSimulation::createTexturedPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
	const Measure<1>& radius, float scale, const std::string& identifier, const Texture& texture)
{
	return std::make_shared<TexturedPlanet>(position, velocity, mass, radius, scale, identifier, shaderManager, texture);
}

std::shared_ptr<ColoredPlanet> StateSpaceSimulation::createColoredPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
	const Measure<1>& radius, float scale, const std::string& identifier, const glm::vec4& color)
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

Measure<1>& StateSpaceSimulation::getSimulationSpeedRef()
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

void StateSpaceSimulation::focusPlanet(std::shared_ptr<Planet> planet)
{
	sceneContext->cameraManager->observePoint(planet->getPositionInWorldSpace().getGlmVec());
}

void StateSpaceSimulation::editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID)
{
	ImGui::Begin(("Simulation settings " + std::to_string(windowID)).c_str());

	ImGui::Checkbox("Render coordinate system axis", &renderCoordinateAxes);
	ImGui::Checkbox("Pause simulation", &pauseSimulation);

	ImGui::Separator();
	ImGui::InputFloat("Simulation speed", simulationSpeed.getValuesPtr());
	ImGui::InputInt("Simulation speed exponent", simulationSpeed.getExponentPtr());

	ImGui::Separator();
	if (ImGui::Button("Close", { ImGui::GetWindowWidth(), 20 })) {
		objectHandler.removeObjectFromEdit(this);
	}

	ImGui::End();
}

void StateSpaceSimulation::renderObject(const Renderable& renderable)
{
	renderable.render(sceneContext);
}

void StateSpaceSimulation::focusCenter(EventDetails* details)
{
	this->focusedPlanet = nullptr;
	sceneContext->cameraManager->observePoint({ 0.0f, 0.0f, 0.0f });
}

void StateSpaceSimulation::switchSimulationState(EventDetails* e)
{
	pauseSimulation = !pauseSimulation;
}

void StateSpaceSimulation::mouseLeftClick(EventDetails* details)
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
			float distanceToIntersection = glm::distance(planet->getPositionInWorldSpace().getGlmVec(), intersectionPoint);

			if (distanceToIntersection < planet->getRadiusInWorldSpace().getGlmVec().x) {

				simulationGui->addObjectToEdit(planet);
			}
		}
	}
}

void StateSpaceSimulation::mouseRightClick(EventDetails* details)
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
			float distanceToIntersection = glm::distance(planet->getPositionInWorldSpace().getGlmVec(), intersectionPoint);

			if (distanceToIntersection < planet->getRadiusInWorldSpace().getGlmVec().x) {
				this->focusedPlanet = planet;

				auto planetInWorldPos = planet->getPositionInWorldSpace().getGlmVec();
				auto newCameraPos = planetInWorldPos - glm::vec3(0, -11 * planet->getRadiusInWorldSpace().getGlmVec()[0], -11 * planet->getRadiusInWorldSpace().getGlmVec()[0]);

				this->getCameraManagerRef().getArcBallCameraRef().setCameraPosition(newCameraPos);
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

