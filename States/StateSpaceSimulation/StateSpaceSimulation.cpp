#include "StateSpaceSimulation.h"

#include "../../Utils/Functions.h"
#include "../../3DObjects/ColoredSphere.h"


#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>


void StateSpaceSimulation::onCreate()
{
	auto shaderManager = stateManager->getContext()->shaderManager;

	auto texturedShader = shaderManager->getShader("texturedObjectShader");
	auto coloredShader = shaderManager->getShader("coloredObjectShader");
	auto axisShader = shaderManager->getShader("coordinateSystemAxes");

	coordinateSystemAxes = std::make_unique<CoordinateSystemAxes>(*axisShader, glm::vec<3, Measure>{ 0.0f, 0.0f, 0.0f });

	auto window = stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::Black);

	auto& settings = Settings::GlobalSettings::getInstance();

	cameraManager = std::make_unique<CameraManagerToSFMLFrameworkAdapter>(settings.getArcBallCameraSettings(),
		settings.getFirstPersonCameraSettings(), window->getRenderWindow());

	mainLight = std::make_unique<Light>(settings.getMainLightSettings());
	simulationGui = std::make_unique<SpaceSimulationImGui>(cameraManager->getArcballCameraSettings(), cameraManager->getFirstPersonCameraSettings(), mainLight->getSettings());

	auto texturesManager = stateManager->getContext()->textureManager;

	shinyMaterial = std::make_unique<Material>(2.0f, 1024.0f);
	dullMaterial = std::make_unique<Material>(0.3f, 4.0f);

	objectsToRender.emplace_back(std::make_unique<TexturedSphere>(*texturedShader, *texturesManager->getTexture("brick"), glm::vec<3, Measure>{ 0.0f, 0.0f, 0.0f }, 36, 36));
	objectsToRender.emplace_back(std::make_unique<TexturedSphere>(*texturedShader, *texturesManager->getTexture("earth"), glm::vec<3, Measure>{ 2.0f, 3.0f, 4.0f }, 36, 36));

	std::vector<GLfloat> ballColors{};

	std::vector<GLfloat> colors((36 + 1) * (36 + 1) * 4);
	for (size_t i = 0; i < colors.size() / 4; i += 1) {

		if (i > 900 && i < 1600) {
			colors[i * 4] = 0.0f;
			colors[i * 4 + 1] = 0.0f;
			colors[i * 4 + 2] = 1.0f;
			colors[i * 4 + 3] = 1.0f;
		}
		else {
			colors[i * 4] = 0.0f;
			colors[i * 4 + 1] = 1.0f;
			colors[i * 4 + 2] = 0.0f;
			colors[i * 4 + 3] = 1.0f;
		}
	}

	objectsToRender.emplace_back(std::make_unique<ColoredSphere>(*coloredShader, glm::vec<3, Measure>{ 0.0f, 0.0f, 0.0f }, 36, 36, glm::vec4({ 0.8f, 0.0f, 0.2f, 1.0f })));
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
	auto shaderManager = stateManager->getContext()->shaderManager;
	auto textureManager = stateManager->getContext()->textureManager;

	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(23.0f), { 0.0, 0.0f, 1.0 });
	model = glm::translate(model, glm::vec3(0.0, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	auto& uniforms0 = objectsToRender[0]->getShader();
	auto& uniforms2 = objectsToRender[2]->getShader();
	auto& uniforms3 = coordinateSystemAxes->getShader();

	uniforms0.useShader();

	auto& uniVals = uniforms0.getUniformLocations();

	mainLight->useLight(uniVals.uniformAmbientIntensity, uniVals.uniformAmbientColor, uniVals.uniformDiffuseIntensity, uniVals.uniformLightDirection);
	cameraManager->useCamera(uniVals.uniformView, uniVals.uniformCameraPosition, uniVals.uniformProjection);
	this->dullMaterial->useMaterial(uniVals.uniformSpecularIntensity, uniVals.uniformShininess);

	objectsToRender[1]->render(uniVals);
	objectsToRender[0]->render(uniVals);


	if (simulationGui->shouldRenderCoordinateSystemAxis()) {

		coordinateSystemAxes->getShader().useShader();

		this->cameraManager->useCamera(uniforms3.getUniformLocations().uniformView, uniforms3.getUniformLocations().uniformCameraPosition, uniforms3.getUniformLocations().uniformProjection);

		this->coordinateSystemAxes->render(uniforms3.getUniformLocations());
	}

	this->stateManager->getContext()->window->renderImGui();
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

