#include "StateSpaceSimulation.h"

#include "../../3DObjects/ColoredPlanet.h"
#include "../../3DObjects/TexturedPlanet.h"

#include <glm/gtc/type_ptr.hpp>

void StateSpaceSimulation::onCreate()
{
	this->shaderManager = stateManager->getContext()->shaderManager;
	this->texturesManager = stateManager->getContext()->textureManager;
	auto axisShader = shaderManager->getShader("coordinateSystemAxes");

	coordinateSystemAxes = std::make_unique<CoordinateSystemAxes>(*axisShader, glm::vec<3, Measure>{ 0.0f, 0.0f, 0.0f });

	auto window = stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::Black);

	auto& settings = Settings::GlobalSettings::getInstance();

	cameraManager = std::make_unique<CameraManagerToSFMLFrameworkAdapter>(settings.getArcBallCameraSettings(),
		settings.getFirstPersonCameraSettings(), window->getRenderWindow());

	mainLight = std::make_unique<Light>(settings.getMainLightSettings());
	simulationGui = std::make_unique<SpaceSimulationImGui>(*this, cameraManager->getArcballCameraSettings(), cameraManager->getFirstPersonCameraSettings(), mainLight->getSettings(), *texturesManager);

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
	cameraManager->updateCameraPosition(static_cast<GLfloat>(time.asSeconds()));
}

void StateSpaceSimulation::draw()
{
	simulationGui->draw();

	for (const auto& el : objectsToRender) {
		renderObject(*el);
	}

	if (simulationGui->shouldRenderCoordinateSystemAxis()) {
		renderObject(*coordinateSystemAxes);
	}

	this->stateManager->getContext()->window->renderImGui();
}

std::shared_ptr<Planet> StateSpaceSimulation::createTexturedPlanet(const glm::vec<3, Measure>& position, const glm::vec<3, Measure>& velocity, const Measure& mass, float scale, const std::string& identifier, const Texture& texture)
{
	return std::make_shared<TexturedPlanet>(position, velocity, mass, scale, identifier, *shaderManager->getShader("texturedObjectShader"), texture);
}

std::shared_ptr<Planet> StateSpaceSimulation::createColoredPlanet(const glm::vec<3, Measure>& position, const glm::vec<3, Measure>& velocity, const Measure& mass, float scale, const std::string& identifier, const glm::vec4& color)
{
	return std::make_shared<ColoredPlanet>(position, velocity, mass, scale, identifier, *shaderManager->getShader("coloredObjectShader"), color);

}

void StateSpaceSimulation::addPlanetToSimulation(std::shared_ptr<Planet> planet)
{
	planets.emplace_back(planet);
	objectsToRender.emplace_back(planet);
}

void StateSpaceSimulation::removePlanetFromSimulation(std::shared_ptr<Planet> planet)
{
	planets.emplace_back(planet);
	objectsToRender.emplace_back(planet);
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

