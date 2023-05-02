#include "FPCamera.h"
#include <glm/ext/matrix_transform.hpp>

FPCamera::FPCamera(Settings::CameraSettings* settings)
	: CameraInterface(settings)
{
	updateCameraProperties();
}


void FPCamera::updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec)
{
	auto velocity = timeInSec * settings->moveSpeed;

	switch (direction)
	{
	case(CameraMoveDirection::Forward):
		settings->position += front * velocity;
		break;
	case(CameraMoveDirection::Backward):
		settings->position -= front * velocity;
		break;
	case(CameraMoveDirection::Left):
		settings->position -= right * velocity;
		break;
	case(CameraMoveDirection::Right):
		settings->position += right * velocity;
		break;
	default:
		break;
	}
	updateCameraProperties();
}

void FPCamera::handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition)
{
	auto change = newMousePosition - oldMousePosition;
	auto xChange = change.x * settings->turnSpeed;
	auto yChange = change.y * settings->turnSpeed;

	settings->yaw += xChange;
	settings->pitch -= yChange;

	if (settings->pitch > 89.0f) {
		settings->pitch = 89.0f;
	}
	else if (settings->pitch < -89.0f) {
		settings->pitch = -89.0f;
	}

	updateCameraProperties();
}

void FPCamera::updateCameraProperties()
{
	front.x = cos(glm::radians(settings->yaw)) * cos(glm::radians(settings->pitch));
	front.y = sin(glm::radians(settings->pitch));
	front.z = sin(glm::radians(settings->yaw)) * cos(glm::radians(settings->pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, settings->worldUp));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 FPCamera::calculateViewMatrix() const
{
	return glm::lookAt(settings->position, settings->position + front, up);
}

void FPCamera::useImmediateGluLookAt()
{
	auto center = settings->position + front;
	gluLookAt(settings->position.x, settings->position.y, settings->position.z,
		center.x, center.y, center.z,
		settings->worldUp.x, settings->worldUp.y, settings->worldUp.y);
}
