#include "Skybox.h"

Skybox::Skybox(std::shared_ptr<CubeMapTexture> skyboxTexture)
	: cubeMapTexture(skyboxTexture)
{
	std::vector<GLfloat> vertices = {
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	std::vector<GLfloat> normals = {
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	};

	std::vector<GLuint> indices = {
		0, 1, 2,
		2, 1, 3,
		2, 3, 5,
		5, 3, 7,
		5, 7, 4,
		4, 7, 6,
		4, 6, 0,
		0, 6, 1,
		4, 0, 5,
		5, 0, 2,
		1, 6, 3,
		3, 6, 7
	};

	mesh.createMesh(vertices, indices, normals);
}

void Skybox::render(SceneContext& sceneContext) const
{
	glDepthMask(GL_FALSE);

	auto shader = sceneContext.shaderManager->useShader("skyboxShader");
	auto camera = sceneContext.cameraManager->getCurrentCamera();
	auto uniforms = shader->getUniformLocations();

	auto viewMatrix = glm::mat4(glm::mat3(camera->getViewMatrix()));
	auto projectionMatrix = camera->getProjectionMatrix();

	glUniformMatrix4fv(uniforms.camera.projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniforms.camera.view, 1, GL_FALSE, glm::value_ptr(viewMatrix));


	cubeMapTexture->useTexture();
	mesh.useMesh();

	glDepthMask(GL_TRUE);
}

