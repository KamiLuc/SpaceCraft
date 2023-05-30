#include "StateSpaceSimulation.h"

#include "../../3DObjects/ColoredPlanet.h"
#include "../../3DObjects/TexturedPlanet.h"

#include <glm/gtc/type_ptr.hpp>

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

	Measure<1> gc(6.67430f, -11);

	if (!pauseSimulation && planets.size() > 1) {

		for (size_t i = 0; i < planets.size(); ++i) {

			for (size_t j = i + 1; j < planets.size(); ++j) {

				auto& planet = planets[i];
				auto& otherPlanet = planets[j];

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

			planets[i]->updatePosition(simTime);
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

std::shared_ptr<Planet> StateSpaceSimulation::createTexturedPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
	const Measure<1>& radius, float scale, const std::string& identifier, const Texture& texture)
{
	return std::make_shared<TexturedPlanet>(position, velocity, mass, radius, scale, identifier, *shaderManager->getShader("texturedObjectShader"), texture);
}

std::shared_ptr<Planet> StateSpaceSimulation::createColoredPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
	const Measure<1>& radius, float scale, const std::string& identifier, const glm::vec4& color)
{
	return std::make_shared<ColoredPlanet>(position, velocity, mass, radius, scale, identifier, *shaderManager->getShader("coloredObjectShader"), color);

}

std::vector<std::shared_ptr<Planet>>& StateSpaceSimulation::getPlanetsRef()
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
	objectsToRender.emplace_back(planet);
}

void StateSpaceSimulation::removePlanetFromSimulation(std::shared_ptr<Planet> planet)
{
	for (auto i = planets.begin(); i != planets.end(); i++) {
		if (*i == planet) {
			planets.erase(i);
			break;
		}
	}

	for (auto i = objectsToRender.begin(); i != objectsToRender.end(); i++) {
		if (*i == planet) {
			objectsToRender.erase(i);
			break;
		}
	}
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
}

