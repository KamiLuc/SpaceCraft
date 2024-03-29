#define _USE_MATH_DEFINES

#include "ArcBallCamera.h"

ArcBallCamera::ArcBallCamera(const Settings::CameraSettings& settings, const glm::vec2& windowSize)
	: CameraInterface(settings)
	, viewMatrix(1.0f)
	, windowSize(windowSize)
{
	updateCameraProperties();
}

void ArcBallCamera::updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec)
{
	if (direction == CameraMoveDirection::Forward)
	{
		auto newPosition = position + getViewDirection() * timeInSec * moveSpeed;
		if (glm::distance(newPosition, lookAt) > 0.1f)
		{
			position = newPosition;
		}
	}
	else if (direction == CameraMoveDirection::Backward)
	{
		position -= getViewDirection() * timeInSec * moveSpeed;
	}

	updateCameraProperties();
}

void ArcBallCamera::handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition)
{
	glm::vec4 position(this->position.x, this->position.y, this->position.z, 1);
	glm::vec4 pivot(lookAt.x, lookAt.y, lookAt.z, 1);

	float deltaAngleX = static_cast<float>((2 * M_PI / windowSize.x)) * turnSpeed;
	float deltaAngleY = static_cast<float>((M_PI / windowSize.y)) * turnSpeed;

	float xAngle = (oldMousePosition.x - newMousePosition.x) * deltaAngleX;
	float yAngle = (oldMousePosition.y - newMousePosition.y) * deltaAngleY;

	float cosAngle = glm::dot(getViewDirection(), worldUp);
	if (cosAngle < -0.99f)
	{
		yAngle = 0.01f;
	}
	if (cosAngle > 0.99f)
	{
		yAngle = -0.01f;
	}

	glm::mat4x4 rotationMatrixX(1.0f);
	rotationMatrixX = glm::rotate(rotationMatrixX, xAngle, worldUp);
	position = (rotationMatrixX * (position - pivot)) + pivot;

	glm::mat4x4 rotationMatrixY(1.0f);
	rotationMatrixY = glm::rotate(rotationMatrixY, yAngle, getRightVector());
	this->position = (rotationMatrixY * (position - pivot)) + pivot;

	updateCameraProperties();
}

glm::mat4 ArcBallCamera::getViewMatrix() const
{
	return viewMatrix;
}

void ArcBallCamera::useImmediateGluLookAt()
{
	gluLookAt(position.x, position.y, position.z,
			  0, 0, 0,
			  worldUp.x, worldUp.y, worldUp.z);
}

glm::vec3 ArcBallCamera::getViewDirection() const
{
	return -glm::transpose(viewMatrix)[2];
}

glm::vec3 ArcBallCamera::getRightVector() const
{
	return glm::transpose(viewMatrix)[0];
}

void ArcBallCamera::editViaGui()
{
	ImGui::DragFloat("Move speed", &moveSpeed, 1.0f, 0.0f, 10000.0f);
	ImGui::DragFloat("Turn speed", &turnSpeed, 0.01f, 0.0f, 10000.0f);
}

void ArcBallCamera::updateCameraProperties()
{
	viewMatrix = glm::lookAt(position, lookAt, worldUp);
}
