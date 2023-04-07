#include "ArcBallCamera.h"

ArcBallCamera::ArcBallCamera(GLfloat distance, glm::vec3 worldUp, GLfloat moveSpeed, GLfloat turnSpeed)
	: CameraInterface(glm::vec3(0.0f, 0.0f, 0.0f), worldUp, moveSpeed, turnSpeed), rotation(), position(), up(), distance(distance)
{
	this->updateCameraProperties();
}

void ArcBallCamera::updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec)
{
	if (direction == CameraMoveDirection::Forward)
	{
		this->distance -= timeInSec * this->moveSpeed;
	}
	else if (direction == CameraMoveDirection::Backward)
	{
		this->distance += timeInSec * this->moveSpeed;
	}

	this->updateCameraProperties();
}

void ArcBallCamera::handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition)
{
	auto change = newMousePosition - oldMousePosition;

	glm::quat xRotation = glm::angleAxis(-change.y * this->turnSpeed, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::quat yRotation = glm::angleAxis(change.x * this->turnSpeed, glm::vec3(0.0f, 1.0f, 0.0f));

	this->rotation = glm::normalize(yRotation * xRotation * this->rotation);

	this->updateCameraProperties();
}

glm::mat4 ArcBallCamera::calculateViewMatrix() const
{
	return glm::lookAt(this->position, glm::vec3(0.0f), this->up);
}

void ArcBallCamera::updateCameraProperties()
{
	this->position = this->rotation * glm::vec3(0.0f, 0.0f, this->distance);
	this->up = this->rotation * glm::vec3(0.0f, 1.0f, 0.0f);
}
