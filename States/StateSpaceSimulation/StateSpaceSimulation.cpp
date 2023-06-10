#include "StateSpaceSimulation.h"

StateSpaceSimulation::StateSpaceSimulation(StateManager* stateManager, Render render)
	: BaseState(stateManager, render)
	, simulationSpeed(8.64f, 4)
	, gravitationalConstant(6.67430f, -11)
	, pauseSimulation(true)
	, renderCoordinateAxes(true)
	, shaderManager(nullptr)
	, texturesManager(nullptr)
{
}

void StateSpaceSimulation::onCreate()
{
	this->shaderManager = stateManager->getContext()->shaderManager;
	this->texturesManager = stateManager->getContext()->textureManager;
	auto axisShader = shaderManager->getShader("coordinateSystemAxes");

	coordinateSystemAxes = std::make_unique<CoordinateSystemAxes>(*axisShader, Measure<3>({ 0.0f, 0.0f, 0.0f }));

	auto window = stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::Black);

	auto& settings = Settings::GlobalSettings::getInstance();

	cameraManager = std::make_unique<CameraManagerToSFMLFrameworkAdapter>(settings.getArcBallCameraSettings(),
		settings.getFirstPersonCameraSettings(), window->getRenderWindow());

	mainLight = std::make_unique<Light>(settings.getMainLightSettings());
	simulationGui = std::make_unique<SpaceSimulationImGui>(*this, *texturesManager);

	shinyMaterial = std::make_unique<Material>(2.0f, 1024.0f);
	dullMaterial = std::make_unique<Material>(0.3f, 4.0f);

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
	cameraManager->updateCameraPosition(timeInSec);

	float simTime = timeInSec * static_cast<float>(this->simulationSpeed.getGlmVec()[0]);

	if (!pauseSimulation) {
		auto it = planets.begin();
		for (; it != planets.end()--; ++it) {

			std::list<std::shared_ptr<Planet>>::iterator it2 = it;
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

	this->stateManager->getContext()->window->renderImGui();
}

std::shared_ptr<TexturedPlanet> StateSpaceSimulation::createTexturedPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
	const Measure<1>& radius, float scale, const std::string& identifier, const Texture& texture)
{
	return std::make_shared<TexturedPlanet>(position, velocity, mass, radius, scale, identifier, *shaderManager->getShader("texturedObjectShader"), texture);
}

std::shared_ptr<ColoredPlanet> StateSpaceSimulation::createColoredPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
	const Measure<1>& radius, float scale, const std::string& identifier, const glm::vec4& color)
{
	return std::make_shared<ColoredPlanet>(position, velocity, mass, radius, scale, identifier, *shaderManager->getShader("coloredObjectShader"), color);
}

std::list<std::shared_ptr<Planet>>& StateSpaceSimulation::getPlanetsRef()
{
	return planets;
}

Light& StateSpaceSimulation::getMainLightRef()
{
	return *mainLight;
}

CameraManager& StateSpaceSimulation::getCameraManagerRef()
{
	return *cameraManager;
}

Measure<1>& StateSpaceSimulation::getSimulationSpeedRef()
{
	return simulationSpeed;
}

void StateSpaceSimulation::addPlanetToSimulation(std::shared_ptr<Planet> planet)
{
	planets.emplace_back(planet);
}

void StateSpaceSimulation::addPlanetToRender(std::shared_ptr<Renderable> renderable)
{
	this->objectsToRender.emplace_back(renderable);
}

void StateSpaceSimulation::removePlanetFromSimulation(std::shared_ptr<Planet> planet)
{
	removePlanetFromSimulation(planet.get());
}

void StateSpaceSimulation::removePlanetFromSimulation(Planet* planet)
{
	for (auto i = planets.begin(); i != planets.end(); i++) {
		if (i->get() == planet) {
			planets.erase(i);
			break;
		}
	}
}

void StateSpaceSimulation::removePlanetFromRender(std::shared_ptr<Renderable> renderable)
{
	removePlanetFromRender(renderable.get());
}

void StateSpaceSimulation::removePlanetFromRender(Renderable* renderable)
{
	for (auto i = objectsToRender.begin(); i != objectsToRender.end(); i++) {
		if (i->get() == renderable) {
			objectsToRender.erase(i);
			break;
		}
	}
}

void StateSpaceSimulation::focusPlanet(std::shared_ptr<Planet> planet)
{
	this->cameraManager->observePoint(planet->getPositionInWorldSpace().getGlmVec(), 0.0f);
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
	auto& shader = renderable.getShader();
	shader.useShader();
	auto& uniVals = shader.getUniformLocations();
	mainLight->useLight(uniVals.uniformAmbientIntensity, uniVals.uniformAmbientColor, uniVals.uniformDiffuseIntensity, uniVals.uniformLightDirection);
	cameraManager->useCamera(uniVals.uniformView, uniVals.uniformCameraPosition, uniVals.uniformProjection);
	this->dullMaterial->useMaterial(uniVals.uniformSpecularIntensity, uniVals.uniformShininess);
	renderable.render(uniVals);
}

void StateSpaceSimulation::switchSimulationState(EventDetails* e)
{
	pauseSimulation = !pauseSimulation;
}

#include <iostream>
#include <glm/common.hpp>

void StateSpaceSimulation::mouseClick(EventDetails* details)
{
	if (!ImGui::GetIO().WantCaptureMouse) {
		float x = static_cast<float>(details->mouse.x);
		float y = -static_cast<float>(details->mouse.y);
		float z = 0.5f;
		auto winSize = stateManager->getContext()->window->getRenderWindow()->getSize();
		glm::vec4 viewPort{ 0.0f, 0.0f, winSize.x, winSize.y };
		glm::mat4 projectionMatrix = cameraManager->getProjectionMatrix();

		for (const auto& planet : objectsToRender) {
			glm::vec3 objectPos = glm::unProject(glm::vec3(x, y, z), cameraManager->getViewMatrix() * planet->getModelMatrix(), projectionMatrix, viewPort);
			printf("%f  %f  %f\n", objectPos.x, objectPos.y, objectPos.z);

			auto c = dynamic_cast<Planet*>(planet.get());

			if (c) {
				std::cout << c->getIdentifier() << "\n";
			}
		}
		std::cout << "\n";
	}
}

void StateSpaceSimulation::addCallbacks()
{
	auto eventManager = stateManager->getContext()->eventManager;

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
	eventManager->addCallback<StateSpaceSimulation>(StateType::SpaceSimulation, "Mouse_Left_Click", &StateSpaceSimulation::mouseClick, this);
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
}

