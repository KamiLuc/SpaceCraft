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

	coordinateSystemAxes = std::make_unique<CoordinateSystemAxes>(axisShader);

	auto window = stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::Black);

	auto& settings = Settings::GlobalSettings::getInstance();

	cameraManager = std::make_unique<CameraManagerToSFMLFrameworkAdapter>(settings.getArcBallCameraSettings(),
		settings.getFirstPersonCameraSettings(), window->getRenderWindow());

	mainLight = std::make_unique<Light>(settings.getMainLightSettings());
	simulationGui = std::make_unique<SpaceSimulationImGui>(cameraManager->getArcballCameraSettings(), cameraManager->getFirstPersonCameraSettings(), mainLight->getSettings());

	//createObjects(meshes);
	earthTexture = std::make_unique<Texture>("Textures/earth.jpg");
	brickTexture = std::make_unique<Texture>("Textures/brick.png");
	sunTexture = std::make_unique<Texture>("Textures/sun.jpg");

	brickTexture->loadTexture();
	sunTexture->loadTexture();
	earthTexture->loadTexture();

	shinyMaterial = std::make_unique<Material>(2.0f, 1024.0f);
	dullMaterial = std::make_unique<Material>(0.3f, 4.0f);

	objectsToRender.emplace_back(std::make_unique<TexturedSphere>(texturedShader, 36, 36));
	objectsToRender.emplace_back(std::make_unique<TexturedSphere>(texturedShader, 36, 36));

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

	objectsToRender.emplace_back(std::make_unique<ColoredSphere>(coloredShader, 36, 36, glm::vec4({ 0.8f, 0.0f, 0.2f, 1.0f })));
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

bool renderPlanets = false;
float scale = 1.0f;

void StateSpaceSimulation::draw()
{
	simulationGui->draw();
	auto shaderManager = stateManager->getContext()->shaderManager;

	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(23.0f), { 0.0, 0.0f, 1.0 });
	model = glm::translate(model, glm::vec3(0.0, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	auto shader1 = objectsToRender[0]->getShader();

	if (lastUsedShader != shader1) {
		auto& uniforms = shader1->getUniformLocations();

		shader1->useShader();

		earthTexture->useTexture();
		shinyMaterial->useMaterial(uniforms.uniformSpecularIntensity, uniforms.uniformShininess);
		glUniformMatrix4fv(uniforms.uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		mainLight->useLight(uniforms.uniformAmbientIntensity, uniforms.uniformAmbientColor,
			uniforms.uniformDiffuseIntensity, uniforms.uniformLightDirection);
		cameraManager->useCamera(uniforms.uniformView,
			uniforms.uniformCameraPosition, uniforms.uniformProjection);
	}



	objectsToRender[0]->render();
	stateManager->getContext()->window->renderImGui();

	lastUsedShader = nullptr;

	/*
	if (simulationGui->shouldRenderCoordinateSystemAxis()) {
		auto axisShader = this->coordinateSystemAxes->getShader();
		shaderManager->useShader(axisShader);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		GLfloat m = 100000.0f;
		model = glm::scale(model, glm::vec3(m, m, m));
		glUniformMatrix4fv(axisShader->getUniformLocations().uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		coordinateSystemAxes->render();
	}
	*/
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

