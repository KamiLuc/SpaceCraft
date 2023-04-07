#include "StateSpaceSimulation.h"
#include "../3DRenderer/Shader.h"
#include "../3DRenderer/Mesh.h"
#include "../Utils/Functions.h"
#include "../3DRenderer/Camera/Camera.h"
#include "../3DRenderer/Texture.h"
#include "../3DRenderer/Material.h"
#include "../3DRenderer/Light.h"

#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>


std::vector<Shader*> shaders{};
std::vector<Mesh*> meshes{};
Material shinyMaterial;
Material dullMaterial;
Light mainLight;

GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
uniformAmbientIntensity = 0, uniformAmbientColour = 0, uniformDirection = 0, uniformDiffuseIntensity = 0,
uniformSpecularIntensity = 0, uniformShininess = 0;
glm::mat4 projection;

Texture brickTexture("Textures/brick.png");
Texture dirtTexture("Textures/dirt.png");

void StateSpaceSimulation::onCreate()
{
	auto window = this->stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::Black);

	this->cameraManager = std::make_unique<CameraManagerToSFMLFrameworkAdapter>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f, window->getRenderWindow());

	const std::filesystem::path fShader("Shaders/shader.fragment");
	const std::filesystem::path vShader("Shaders/shader.vertex");

	createObjects(meshes);
	createShaders(shaders, fShader, vShader);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.loadTexture();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.loadTexture();

	shinyMaterial = Material(2.0f, 256);
	dullMaterial = Material(0.3f, 4);

	mainLight = Light(0.0f, 1.0f, 1.0f, 0.2f,
		0.0f, 0.0f, -1.0f, 0.3f);

	this->stateManager->getContext()->eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Start_Camera_Forward", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	this->stateManager->getContext()->eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Stop_Camera_Forward", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	this->stateManager->getContext()->eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Start_Camera_Backward", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	this->stateManager->getContext()->eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Stop_Camera_Backward", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	this->stateManager->getContext()->eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Start_Camera_Left", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	this->stateManager->getContext()->eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Stop_Camera_Left", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	this->stateManager->getContext()->eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Start_Camera_Right", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	this->stateManager->getContext()->eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Stop_Camera_Right", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	this->stateManager->getContext()->eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Enable_Mouse_Camera_Move", &CameraManagerToSFMLFrameworkAdapter::enableMouseCameraMove, this->cameraManager.get());
	this->stateManager->getContext()->eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Disable_Mouse_Camera_Move", &CameraManagerToSFMLFrameworkAdapter::disableMouseCameraMove, this->cameraManager.get());
}

void StateSpaceSimulation::onDestroy()
{
	this->stateManager->getContext()->eventManager->removeCallback(StateType::SpaceSimulation, "Start_Camera_Forward");
	this->stateManager->getContext()->eventManager->removeCallback(StateType::SpaceSimulation, "Stop_Camera_Forward");
	this->stateManager->getContext()->eventManager->removeCallback(StateType::SpaceSimulation, "Start_Camera_Backward");
	this->stateManager->getContext()->eventManager->removeCallback(StateType::SpaceSimulation, "Stop_Camera_Backward");
	this->stateManager->getContext()->eventManager->removeCallback(StateType::SpaceSimulation, "Start_Camera_Left");
	this->stateManager->getContext()->eventManager->removeCallback(StateType::SpaceSimulation, "Stop_Camera_Left");
	this->stateManager->getContext()->eventManager->removeCallback(StateType::SpaceSimulation, "Start_Camera_Right");
	this->stateManager->getContext()->eventManager->removeCallback(StateType::SpaceSimulation, "Stop_Camera_Right");
	this->stateManager->getContext()->eventManager->removeCallback(StateType::SpaceSimulation, "Enable_Mouse_Camera_Move");
	this->stateManager->getContext()->eventManager->removeCallback(StateType::SpaceSimulation, "Disable_Mouse_Camera_Move");
}

void StateSpaceSimulation::activate()
{
}

void StateSpaceSimulation::deactivate()
{
}

void StateSpaceSimulation::update(const sf::Time& time)
{
	this->cameraManager->updateCameraPosition(static_cast<GLfloat>(time.asSeconds()));
}

void StateSpaceSimulation::draw()
{
	shaders[0]->useShader();

	uniformModel = shaders[0]->getModelLocation();
	uniformProjection = shaders[0]->getProjectionLocation();
	uniformView = shaders[0]->getViewLocation();
	uniformAmbientColour = shaders[0]->getAmbientColorLocation();
	uniformAmbientIntensity = shaders[0]->getAmbientIntensityLocation();
	uniformDirection = shaders[0]->getLightDirectionLocation();
	uniformDiffuseIntensity = shaders[0]->getDiffuseIntensityLocation();
	uniformEyePosition = shaders[0]->getCameraPositionLocation();
	uniformSpecularIntensity = shaders[0]->getSpecularIntensityLocation();
	uniformShininess = shaders[0]->getShininessLocation();

	mainLight.useLight(uniformAmbientIntensity, uniformAmbientColour,
		uniformDiffuseIntensity, uniformDirection);

	this->cameraManager->useCamera(uniformView, uniformEyePosition, uniformProjection);

	glm::mat4 model(1.0f);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
	//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brickTexture.useTexture();
	shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
	meshes[0]->renderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
	//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	dirtTexture.useTexture();
	dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
	meshes[1]->renderMesh();

	glUseProgram(0);
}
