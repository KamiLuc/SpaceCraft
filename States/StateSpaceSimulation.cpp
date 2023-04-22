#include "StateSpaceSimulation.h"
#include "../3DRenderer/Shader/Shader.h"
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
	auto window = stateManager->getContext()->window;
	auto windowSize = window->getWindowSize();
	window->setClearColor(sf::Color::Black);

	cameraManager = std::make_unique<CameraManagerToSFMLFrameworkAdapter>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 270.0f, 0.0f, 5.0f, 0.5f, window->getRenderWindow());

	createObjects(meshes);



	earthTexture = Texture("Textures/earth.jpg");
	earthTexture.loadTexture();
	sunTexture = Texture("Textures/sun.jpg");
	sunTexture.loadTexture();
	brickTexture.loadTexture();

	shinyMaterial = Material(2.0f, 1024);
	dullMaterial = Material(0.3f, 4);

	mainLight = Light(1.0f, 1.0f, 1.0f, 0.3f,
		0.0f, 0.0f, -1.0f, 0.9f);

	//sun = new Sphere(36, 36, 0.004654f);
	//earth = new Sphere(36, 36, 0.0000426f);

	earth = new Sphere(36, 36, 0.5f);
	sun = new Sphere(36, 36, 0.2f);

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
	auto shader = stateManager->getContext()->shaderManager->getShader("shader");

	if (shader) {
		stateManager->getContext()->shaderManager->useShader(shader);
		uniformModel = shader->getModelLocation();
		uniformProjection = shader->getProjectionLocation();
		uniformView = shader->getViewLocation();
		uniformAmbientColour = shader->getAmbientColorLocation();
		uniformAmbientIntensity = shader->getAmbientIntensityLocation();
		uniformDirection = shader->getLightDirectionLocation();
		uniformDiffuseIntensity = shader->getDiffuseIntensityLocation();
		uniformEyePosition = shader->getCameraPositionLocation();
		uniformSpecularIntensity = shader->getSpecularIntensityLocation();
		uniformShininess = shader->getShininessLocation();
	}

	mainLight.useLight(uniformAmbientIntensity, uniformAmbientColour,
		uniformDiffuseIntensity, uniformDirection);

	cameraManager->useCamera(uniformView, uniformEyePosition, uniformProjection);


	glm::mat4 model(1.0f);
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
	stateManager->getContext()->shaderManager->endDrawLoop();
}
