#include "StateSpaceSimulation.h"
#include <glm/gtc/type_ptr.hpp>

#include "../Utils/Functions.h"

void StateSpaceSimulation::onCreate()
{
	auto window = stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::Black);

	cameraManager = std::make_unique<CameraManagerToSFMLFrameworkAdapter>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 270.0f, 0.0f, 5.0f, 0.5f, window->getRenderWindow());
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

	earth = std::make_unique<Sphere>(36, 36, 0.5f);
	sun = std::make_unique<Sphere>(36, 36, 0.2f);

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

float angle = 0.0;

void StateSpaceSimulation::draw()
{
	changeShader("texturedObjectShader");

	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(angle), { 0.0, 0.0f, 1.0 });
	model = glm::translate(model, glm::vec3(0.0, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));

	if (currentUniformLocations) {

		glUniformMatrix4fv(currentUniformLocations->uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		earthTexture->useTexture();
		shinyMaterial->useMaterial(currentUniformLocations->uniformSpecularIntensity, currentUniformLocations->uniformShininess);
		//meshes[0]->renderMesh();

		earth->renderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-5.0f, 0.0f, -2.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		glUniformMatrix4fv(currentUniformLocations->uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		sunTexture->useTexture();
		dullMaterial->useMaterial(currentUniformLocations->uniformSpecularIntensity, currentUniformLocations->uniformShininess);
		sun->renderMesh();


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
	}
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

