#include "StateSpaceSimulation.h"
#include "../3DRenderer/Shader.h"
#include "../3DRenderer/Mesh.h"
#include "../Utils/Functions.h"
#include "../3DRenderer/Texture.h"
#include "../3DRenderer/Material.h"
#include "../3DRenderer/Light.h"

#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

//to delete
#include "../3DObjects/Sphere.h"

std::vector<Shader*> shaders{};
std::vector<Mesh*> meshes{};
Material shinyMaterial;
Material dullMaterial;
Light mainLight;

Sphere* earth;
Sphere* sun;
Mesh* mesh;

GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
uniformAmbientIntensity = 0, uniformAmbientColour = 0, uniformDirection = 0, uniformDiffuseIntensity = 0,
uniformSpecularIntensity = 0, uniformShininess = 0;
glm::mat4 projection;

Texture earthTexture("Textures/brick.png");
Texture sunTexture("Textures/brick.png");
Texture brickTexture("Textures/brick.png");


void StateSpaceSimulation::onCreate()
{
	auto window = this->stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::Black);

	this->cameraManager = std::make_unique<CameraManagerToSFMLFrameworkAdapter>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 270.0f, 0.0f, 5.0f, 0.5f, window->getRenderWindow());

	const std::filesystem::path fShader("Shaders/shader.fragment");
	const std::filesystem::path vShader("Shaders/shader.vertex");

	createObjects(meshes);
	createShaders(shaders, fShader, vShader);


	mesh = new Mesh();

	GLfloat veritces[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f };
	GLuint indices[] = { 0,1,2 };

	mesh->createMesh(veritces, indices, 21, 3);

	earthTexture = Texture("Textures/earth.jpg");
	earthTexture.loadTexture();
	sunTexture = Texture("Textures/sun.jpg");
	sunTexture.loadTexture();
	brickTexture.loadTexture();

	shinyMaterial = Material(2.0f, 256);
	dullMaterial = Material(0.3f, 4);

	mainLight = Light(1.0f, 1.0f, 1.0f, 0.3f,
		0.0f, 0.0f, -1.0f, 0.3f);

	//sun = new Sphere(36, 36, 0.004654f);
	//earth = new Sphere(36, 36, 0.0000426f);

	earth = new Sphere(36, 36, 0.5f);
	sun = new Sphere(36, 36, 0.2f);

	auto eventManager = this->stateManager->getContext()->eventManager;

	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Start_Camera_Forward", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Stop_Camera_Forward", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Start_Camera_Backward", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Stop_Camera_Backward", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Start_Camera_Left", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Stop_Camera_Left", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Start_Camera_Right", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Stop_Camera_Right", &CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput, this->cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Enable_Mouse_Camera_Move", &CameraManagerToSFMLFrameworkAdapter::enableMouseCameraMove, this->cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Disable_Mouse_Camera_Move", &CameraManagerToSFMLFrameworkAdapter::disableMouseCameraMove, this->cameraManager.get());
	eventManager->addCallback<CameraManagerToSFMLFrameworkAdapter>(StateType::SpaceSimulation, "Change_Camera", &CameraManagerToSFMLFrameworkAdapter::changeCamera, this->cameraManager.get());
}

void StateSpaceSimulation::onDestroy()
{
	auto eventManager = this->stateManager->getContext()->eventManager;

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
	this->cameraManager->updateCameraPosition(static_cast<GLfloat>(time.asSeconds()));
}

float angle = 0.0;

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
	model = glm::scale(model, glm::vec3(100.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	earthTexture.useTexture();
	shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
	mesh->renderMesh();

	model = glm::mat4(1.0f);

	model = glm::rotate(model, glm::radians(angle), { 0.0, 0.0f, 1.0 });
	model = glm::translate(model, glm::vec3(0.0, 0.0f, 0.0f));
	//angle += 0.01f;

	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	earthTexture.useTexture();
	shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
	//meshes[0]->renderMesh();
	earth->renderMesh();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-5.0f, 0.0f, -2.0f));
	model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	sunTexture.useTexture();
	dullMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
	sun->renderMesh();


	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(3.0f, 3.0f, 3.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	brickTexture.useTexture();
	shinyMaterial.useMaterial(uniformSpecularIntensity, uniformShininess);
	meshes[0]->renderMesh();

	glUseProgram(0);
}
