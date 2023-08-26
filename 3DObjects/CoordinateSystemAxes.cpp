#include "CoordinateSystemAxes.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

CoordinateSystemAxes::CoordinateSystemAxes(std::shared_ptr<ShaderManager> shaderManager, const glm::vec3& position, float lineWidth , bool immediateRender)
	: VAO(-1)
	, VBO(-1)
	, Renderable(shaderManager)
	, Moveable(position)
	, model(1.0f)
	, lineWidth(lineWidth)
	, immediateRender(immediateRender)
	, position(position)
{
	model = glm::translate(model, position);

	GLfloat axisVertices[] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
}

void CoordinateSystemAxes::render(std::shared_ptr<SceneContext> sceneContext) const
{
	if (immediateRender) {
		renderWithImmediateMode(sceneContext);
		return;
	}

	auto shader = shaderManager->getShader("coordinateSystemAxes");
	auto& uniforms = shader->getUniformLocations();
	
	if (shader != shaderManager->getLastUsedShader())
	{
		shader->useShader();
		shaderManager->setLastUsedShader(shader);
	}

	sceneContext->cameraManager->useCamera(uniforms.uniformView, uniforms.uniformCameraPosition, uniforms.uniformProjection);

	glUniformMatrix4fv(shader->getUniformLocations().uniformModel, 1, GL_FALSE, glm::value_ptr(this->getModelMatrix()));
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 6);
	glBindVertexArray(0);
}

glm::mat4 CoordinateSystemAxes::getModelMatrix() const
{
	GLfloat m = 1000.0f;
	return glm::scale(model, glm::vec3(m, m, m));
}

void CoordinateSystemAxes::setPosition(const glm::vec3& position)
{
	this->position = position;
	this->model = glm::translate(glm::mat4(1.0f), position);
}

void CoordinateSystemAxes::renderWithImmediateMode(std::shared_ptr<SceneContext> sceneContext) const
{
	glPushMatrix();

	glLineWidth(lineWidth);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(sceneContext->cameraManager->getProjectionMatrix()));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(sceneContext->cameraManager->getViewMatrix()));

	glBegin(GL_LINES);

	glColor3f(0.2f, 0.0f, 0.0f);
	glVertex3f(-1000.0f + position.x, 0.0f, 0.0f); 
	glVertex3f(-1.0f + position.x, 0.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f + position.x, 0.0f, 0.0f);
	glVertex3f(1000.0f + position.x, 0.0f, 0.0f);

	glColor3f(0.0f, 0.2f, 0.0f);
	glVertex3f(0.0f, -1000.0f + position.y, 0.0f);
	glVertex3f(0.0f, -1.0f + position.y, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f + position.y, 0.0f);
	glVertex3f(0.0f, 1000.0f + position.y, 0.0f);

	glColor3f(0.0f, 0.0f, 0.2f);
	glVertex3f(0.0f, 0.0f, -1000.0f + position.z);
	glVertex3f(0.0f, 0.0f, -1.0f + position.z);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f + position.z);
	glVertex3f(0.0f, 0.0f, 1000.0f + position.z);
	glEnd();

	glPopMatrix();
}
