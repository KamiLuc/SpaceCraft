#include "CoordinateSystemAxes.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

CoordinateSystemAxes::CoordinateSystemAxes(const glm::vec3& position, float lineWidth, bool immediateRender)
	: VAO(0)
	, VBO(0)
	, Moveable(PhysicalUnitVec<3>(position))
	, model(1.0f)
	, lineWidth(lineWidth)
	, immediateRender(immediateRender)
	, position(position)
{
	model = glm::translate(model, position);

	GLfloat axisVertices[] = {
		-1000.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1000.0f, 0.0f, 0.0f,

		0.0f, -1000.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1000.0f, 0.0f,

		0.0f, 0.0f, -1000.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1000.0f
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

CoordinateSystemAxes::~CoordinateSystemAxes()
{
	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
}

void CoordinateSystemAxes::render(SceneContext& sceneContext) const
{
	if (immediateRender)
	{
		renderWithImmediateMode(sceneContext);
		return;
	}

	glPushMatrix();
	glLineWidth(lineWidth);

	auto shader = sceneContext.shaderManager->useShader("coordinateSystemAxes");
	shader->useCamera(*sceneContext.cameraManager->getCurrentCamera());
	shader->useModel(getModelMatrix());

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 12);
	glBindVertexArray(0);

	glLineWidth(1.0f);
	glPopMatrix();
}

glm::mat4 CoordinateSystemAxes::getModelMatrix() const
{
	return model;
}

void CoordinateSystemAxes::setPosition(const glm::vec3& position)
{
	this->position = position;
	this->model = glm::translate(glm::mat4(1.0f), position);
}

void CoordinateSystemAxes::renderWithImmediateMode(SceneContext& sceneContext) const
{
	glPushMatrix();

	glLineWidth(lineWidth);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(sceneContext.cameraManager->getCurrentCamera()->getProjectionMatrix()));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(glm::value_ptr(sceneContext.cameraManager->getCurrentCamera()->getViewMatrix()));

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
