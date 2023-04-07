#include "CameraManager.h"
#include <glm/gtc/type_ptr.hpp>

CameraManager::CameraManager(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed, GLfloat aspectRatio)
	: aspectRatio(aspectRatio), moveSpeed(moveSpeed), turnSpeed(turnSpeed), camera(position, up, yaw, pitch), cameraMoveDirections{}
{
	this->calculateProjectionMatrix();
}

void CameraManager::addCameraMoveDirection(const CameraMoveDirection& direction)
{
	if (std::find(this->cameraMoveDirections.begin(), this->cameraMoveDirections.end(), direction) == this->cameraMoveDirections.end())
	{
		this->cameraMoveDirections.push_back(direction);
	}
}

void CameraManager::removeCameraMoveDirection(const CameraMoveDirection& direction)
{
	this->cameraMoveDirections.remove(direction);
}

void CameraManager::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= this->turnSpeed;
	yChange *= this->turnSpeed;

	this->camera.yaw += xChange;
	this->camera.pitch -= yChange;

	if (this->camera.pitch > 89.0f) {
		this->camera.pitch = 89.0f;
	}
	else if (this->camera.pitch < -89.0f) {
		this->camera.pitch = -89.0f;
	}

	this->camera.updateCameraProperties();
}

void CameraManager::updateCameraPosition(const GLfloat& timeInSec)
{
	auto velocity = timeInSec * this->moveSpeed;

	if (this->cameraMoveDirections.empty())
	{
		return;
	}

	for (const auto& it : this->cameraMoveDirections)
	{
		switch (it)
		{
		case(CameraMoveDirection::Forward):
			this->camera.position += camera.front * velocity;
			break;
		case(CameraMoveDirection::Backward):
			this->camera.position -= camera.front * velocity;
			break;
		case(CameraMoveDirection::Left):
			this->camera.position -= camera.right * velocity;
			break;
		case(CameraMoveDirection::Right):
			this->camera.position += camera.right * velocity;
			break;
		default:
			break;
		}
	}
	this->camera.updateCameraProperties();
}

void CameraManager::useCamera(GLuint uniformView, GLuint uniformEyePosition, GLuint uniformProjection)
{
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(this->camera.calculateViewMatrix()));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));
	auto cPos = this->camera.getPosition();
	glUniform3f(uniformEyePosition, cPos.x, cPos.y, cPos.z);
}

void CameraManager::calculateProjectionMatrix()
{
	this->projectionMatrix = glm::perspective(glm::radians(45.0f), this->aspectRatio, 0.1f, 1000.0f);
}
