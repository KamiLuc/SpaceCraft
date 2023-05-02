#include "StateSpaceSimulation.h"
#include <glm/gtc/type_ptr.hpp>

#include "../Utils/Functions.h"
#include "../3DObjects/ColoredSphere.h"
#include <imgui.h>

void StateSpaceSimulation::onCreate()
{
	auto window = stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::Black);

	auto& settings = Settings::GlobalSettings::getInstance();

	cameraManager = std::make_unique<CameraManagerToSFMLFrameworkAdapter>(settings.getArcBallCameraSettings(),
		settings.getFirstPersonCameraSettings(), window->getRenderWindow());

	mainLight = std::make_unique<Light>(1.0f, 1.0f, 1.0f, 0.3f, 0.0f, 0.0f, -1.0f, 0.9f);

	createObjects(meshes);
	earthTexture = std::make_unique<Texture>("Textures/earth.jpg");
	brickTexture = std::make_unique<Texture>("Textures/brick.png");
	sunTexture = std::make_unique<Texture>("Textures/sun.jpg");

	brickTexture->loadTexture();
	sunTexture->loadTexture();
	earthTexture->loadTexture();

	shinyMaterial = std::make_unique<Material>(2.0f, 1024.0f);
	dullMaterial = std::make_unique<Material>(0.3f, 4.0f);

	earth = std::make_unique<TexturedSphere>(36, 36);
	sun = std::make_unique<TexturedSphere>(36, 36);

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

	ball = std::make_unique<ColoredSphere>(36, 36, glm::vec4({ 0.8f, 0.0f, 0.2f, 1.0f }));

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

void StateSpaceSimulation::onDestroy()
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
	changeShader("texturedObjectShader");

	auto& setting = Settings::GlobalSettings::getInstance();

	ImGui::SetNextWindowSize(ImVec2(300.0f, 120.0f));
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::Begin("Camera settings", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::Text(setting.getFirstPersonCameraSettings()->cameraName.c_str());
	ImGui::SliderFloat("Turn speed", &setting.getFirstPersonCameraSettings()->turnSpeed, 0.1f, 2.0f);
	ImGui::SliderFloat("Move speed", &setting.getFirstPersonCameraSettings()->moveSpeed, 0.0f, 20.f);
	ImGui::End();

	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(23.0f), { 0.0, 0.0f, 1.0 });
	model = glm::translate(model, glm::vec3(0.0, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));

	if (currentUniformLocations) {

		if (renderPlanets) {
			glUniformMatrix4fv(currentUniformLocations->uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			earthTexture->useTexture();
			shinyMaterial->useMaterial(currentUniformLocations->uniformSpecularIntensity, currentUniformLocations->uniformShininess);
			//meshes[0]->renderMesh();

			earth->renderMesh();

			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-5.0f, 0.0f, -2.0f));
			model = glm::scale(model, glm::vec3(scale, scale, scale));
			glUniformMatrix4fv(currentUniformLocations->uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			sunTexture->useTexture();
			dullMaterial->useMaterial(currentUniformLocations->uniformSpecularIntensity, currentUniformLocations->uniformShininess);
			sun->renderMesh();
		}

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(currentUniformLocations->uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		brickTexture->useTexture();
		shinyMaterial->useMaterial(currentUniformLocations->uniformSpecularIntensity, currentUniformLocations->uniformShininess);
		meshes[0]->renderMesh();
	}

	changeShader("coloredObjectShader");

	if (currentUniformLocations) {
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(currentUniformLocations->uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		shinyMaterial->useMaterial(currentUniformLocations->uniformSpecularIntensity, currentUniformLocations->uniformShininess);
		meshes[1]->renderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.0f, -1.0f, -5.0f));
		glUniformMatrix4fv(currentUniformLocations->uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ball->renderMesh();
	}

	stateManager->getContext()->window->start2D();
	stateManager->getContext()->window->drawImGui();
}

void StateSpaceSimulation::changeShader(const std::string& shaderName)
{
	auto shaderManager = stateManager->getContext()->shaderManager;

	auto shader = shaderManager->getShader(shaderName);

	if (shader) {
		shaderManager->useShader(shader);

		currentUniformLocations = &shader->getUniformLocations();
		mainLight->useLight(currentUniformLocations->uniformAmbientIntensity, currentUniformLocations->uniformAmbientColor,
			currentUniformLocations->uniformDiffuseIntensity, currentUniformLocations->uniformLightDirection);
		cameraManager->useCamera(currentUniformLocations->uniformView,
			currentUniformLocations->uniformCameraPosition, currentUniformLocations->uniformProjection);
	}
	else {
		currentUniformLocations = nullptr;
	}
}

