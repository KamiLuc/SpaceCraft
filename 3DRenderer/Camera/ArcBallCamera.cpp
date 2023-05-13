#define _USE_MATH_DEFINES

#include "ArcBallCamera.h"

#include <cmath>

ArcBallCamera::ArcBallCamera(const Settings::CameraSettings& settings, const glm::vec2& windowSize)
	: CameraInterface(settings), viewMatrix(1.0f), windowSize(windowSize)
{
	updateCameraProperties();
}

void ArcBallCamera::updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec)
{
	if (direction == CameraMoveDirection::Forward)
	{
		auto newPosition = settings.position + getViewDirection() * timeInSec * settings.moveSpeed;
		if (glm::distance(newPosition, settings.lookAt) > 0.1f) {
			settings.position = newPosition;
		}
	}
	else if (direction == CameraMoveDirection::Backward)
	{
		settings.position -= getViewDirection() * timeInSec * settings.moveSpeed;
	}

	updateCameraProperties();
}

void ArcBallCamera::handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition)
{
	glm::vec4 position(settings.position.x, settings.position.y, settings.position.z, 1);
	glm::vec4 pivot(settings.lookAt.x, settings.lookAt.y, settings.lookAt.z, 1);

	float deltaAngleX = static_cast<float>((2 * M_PI / windowSize.x)) * settings.turnSpeed;
	float deltaAngleY = static_cast<float>((M_PI / windowSize.y)) * settings.turnSpeed;

	float xAngle = (oldMousePosition.x - newMousePosition.x) * deltaAngleX;
	float yAngle = (oldMousePosition.y - newMousePosition.y) * deltaAngleY;

	float cosAngle = glm::dot(getViewDirection(), settings.worldUp);
	if (cosAngle < -0.99f) {
		yAngle = 0.01f;
	}
	if (cosAngle > 0.99f) {
		yAngle = -0.01f;
	}

	glm::mat4x4 rotationMatrixX(1.0f);
	rotationMatrixX = glm::rotate(rotationMatrixX, xAngle, settings.worldUp);
	position = (rotationMatrixX * (position - pivot)) + pivot;

	glm::mat4x4 rotationMatrixY(1.0f);
	rotationMatrixY = glm::rotate(rotationMatrixY, yAngle, getRightVector());
	settings.position = (rotationMatrixY * (position - pivot)) + pivot;

	updateCameraProperties();
}

glm::mat4 ArcBallCamera::calculateViewMatrix() const
{
	return viewMatrix;
}

void ArcBallCamera::useImmediateGluLookAt()
{
	gluLookAt(settings.position.x, settings.position.y, settings.position.z,
		0, 0, 0,
		settings.worldUp.x, settings.worldUp.y, settings.worldUp.z);
}

glm::vec3 ArcBallCamera::getViewDirection() const
{
	return -glm::transpose(viewMatrix)[2];
}

glm::vec3 ArcBallCamera::getRightVector() const
{
	return glm::transpose(viewMatrix)[0];
}

void ArcBallCamera::updateCameraProperties()
{
	viewMatrix = glm::lookAt(settings.position, settings.lookAt, settings.worldUp);
}

