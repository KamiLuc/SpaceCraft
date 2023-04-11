#define _USE_MATH_DEFINES

#include "ArcBallCamera.h"

#include <cmath>

ArcBallCamera::ArcBallCamera(GLfloat distance, glm::vec3 worldUp, GLfloat moveSpeed, GLfloat turnSpeed)
	: CameraInterface(glm::vec3(0.0f, 0.0f, distance + 5.0f), worldUp, moveSpeed, turnSpeed),
	rotation(1.0f), viewport(viewport), distance(distance), lookAt(0.0f, 0.0f, 0.0f)
{
	this->updateCameraProperties();
}

void ArcBallCamera::updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec)
{
	if (direction == CameraMoveDirection::Forward)
	{
		if (this->distance - timeInSec * this->moveSpeed >= 0)
		{
			this->distance -= timeInSec * this->moveSpeed;
		}
	}
	else if (direction == CameraMoveDirection::Backward)
	{
		this->distance += timeInSec * this->moveSpeed;
	}

	this->updateCameraProperties();
}

void ArcBallCamera::handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition)
{
	glm::vec2 delta = newMousePosition - oldMousePosition;
	glm::mat4 rotationMatrix(1.0f);

	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(delta.x * turnSpeed), this->worldUp);
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(-delta.y * turnSpeed), glm::normalize(glm::cross(this->worldUp, this->position)));

	this->position = glm::vec3(rotationMatrix * glm::vec4(this->position, 1.0f));
	this->worldUp = glm::vec3(rotationMatrix * glm::vec4(this->worldUp, 0.0f));

	this->updateCameraProperties();
}

glm::mat4 ArcBallCamera::calculateViewMatrix() const
{
	return glm::lookAt(this->position, this->lookAt, this->worldUp);
}

void ArcBallCamera::updateCameraProperties()
{
	this->position = glm::normalize(this->position) * distance;
	this->worldUp = glm::normalize(glm::cross(glm::cross(this->position, this->worldUp), this->position));
}
