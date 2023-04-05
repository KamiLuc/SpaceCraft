#include "Camera.h"

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch)
	: position(startPosition), worldUp(startUp), yaw(startYaw), pitch(startPitch), front(0.0f, 0.0f, -1.0f), up(0)
{
	updateCameraProperties();
}

Camera::~Camera()
{
}

glm::vec3 Camera::getPosition() const
{
	return this->position;
}

glm::mat4 Camera::calculateViewMatrix() const
{
	return glm::lookAt(this->position, this->position + this->front, up);
}

void Camera::updateCameraProperties()
{
	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(pitch));
	this->front.y = sin(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(this->front);

	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}
