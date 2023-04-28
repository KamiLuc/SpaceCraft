#define _USE_MATH_DEFINES

#include "ArcBallCamera.h"

#include <cmath>

ArcBallCamera::ArcBallCamera(GLfloat distance, glm::vec3 worldUp, glm::vec3 lookAt,
	GLfloat moveSpeed, GLfloat turnSpeed, glm::vec2 windowSize)
	: CameraInterface(glm::vec3(0.0f, 0.0f, distance), worldUp, lookAt, moveSpeed, turnSpeed, "Arc ball camera"),
	viewMatrix(1.0f), windowSize(windowSize)
{
	updateCameraProperties();
}

void ArcBallCamera::updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec)
{
	if (direction == CameraMoveDirection::Forward)
	{
		auto newPosition = position + this->getViewDirection() * timeInSec * moveSpeed;
		if (glm::distance(newPosition, lookAt) > 0.1f) {
			position = newPosition;
		}
	}
	else if (direction == CameraMoveDirection::Backward)
	{
		position -= this->getViewDirection() * timeInSec * moveSpeed;
	}

	updateCameraProperties();
}

void ArcBallCamera::handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition)
{
	glm::vec4 position(this->position.x, this->position.y, this->position.z, 1);
	glm::vec4 pivot(this->lookAt.x, this->lookAt.y, this->lookAt.z, 1);

	float deltaAngleX = static_cast<float>((2 * M_PI / this->windowSize.x));
	float deltaAngleY = static_cast<float>((M_PI / this->windowSize.y));

	float xAngle = (oldMousePosition.x - newMousePosition.x) * deltaAngleX;
	float yAngle = (oldMousePosition.y - newMousePosition.y) * deltaAngleY;

	float cosAngle = glm::dot(this->getViewDirection(), this->worldUp);
	if (cosAngle < -0.99f) {
		yAngle = 0.01f;
	}
	if (cosAngle > 0.99f) {
		yAngle = -0.01f;
	}

	glm::mat4x4 rotationMatrixX(1.0f);
	rotationMatrixX = glm::rotate(rotationMatrixX, xAngle, this->worldUp);
	position = (rotationMatrixX * (position - pivot)) + pivot;

	glm::mat4x4 rotationMatrixY(1.0f);
	rotationMatrixY = glm::rotate(rotationMatrixY, yAngle, this->getRightVector());
	this->position = (rotationMatrixY * (position - pivot)) + pivot;

	this->updateCameraProperties();
}

glm::mat4 ArcBallCamera::calculateViewMatrix() const
{
	return this->viewMatrix;
}

void ArcBallCamera::useImmediateGluLookAt()
{
	gluLookAt(position.x, position.y, position.z,
		0, 0, 0,
		worldUp.x, worldUp.y, worldUp.z);
}

glm::vec3 ArcBallCamera::getViewDirection() const
{
	return -glm::transpose(this->viewMatrix)[2];
}

glm::vec3 ArcBallCamera::getRightVector() const
{
	return glm::transpose(this->viewMatrix)[0];
}

void ArcBallCamera::updateCameraProperties()
{
	this->viewMatrix = glm::lookAt(this->position, this->lookAt, this->worldUp);
}

