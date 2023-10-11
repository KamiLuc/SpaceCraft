#include "CameraManager.h"

#include <glm/gtc/type_ptr.hpp>

CameraManager::CameraManager(const Settings::CameraSettings& arcBallCameraSettings, const Settings::CameraSettings& firstPersonCameraSettings, const glm::vec2& windowSize)
	: fpCamera(firstPersonCameraSettings), arcBallCamera(arcBallCameraSettings, windowSize),
	windowSize(windowSize), currentCamera(&arcBallCamera)
{
	calculateProjectionMatrix();
}

void CameraManager::addCameraMoveDirection(const CameraMoveDirection& direction)
{
	if (std::find(cameraMoveDirections.begin(), cameraMoveDirections.end(), direction) == cameraMoveDirections.end())
	{
		cameraMoveDirections.push_back(direction);
	}
}

void CameraManager::removeCameraMoveDirection(const CameraMoveDirection& direction)
{
	cameraMoveDirections.remove(direction);
}

void CameraManager::mouseControl(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition)
{
	currentCamera->handleMouse(oldMousePosition, newMousePosition);
}

void CameraManager::updateCameraPosition(const GLfloat& timeInSec)
{
	for (const auto& it : cameraMoveDirections)
	{
		currentCamera->updateCameraPosition(it, timeInSec);
	}
}

void CameraManager::useCamera(GLuint uniformView, GLuint uniformEyePosition, GLuint uniformProjection)
{
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(currentCamera->calculateViewMatrix()));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	auto cPos = currentCamera->getPosition();
	glUniform3f(uniformEyePosition, cPos.x, cPos.y, cPos.z);
}

void CameraManager::changeCamera()
{
	if (!ImGui::GetIO().WantCaptureKeyboard)
	{
		if (currentCamera == &arcBallCamera)
		{
			currentCamera = &fpCamera;
		}
		else
		{
			currentCamera = &arcBallCamera;
		}
	}
}

void CameraManager::observePoint(const glm::vec3& point)
{
	arcBallCamera.setLookAt(point);
	arcBallCamera.updateCameraProperties();
	fpCamera.setLookAt(point);
}

FPCamera& CameraManager::getFirstPersonCameraRef()
{
	return fpCamera;
}

ArcBallCamera& CameraManager::getArcBallCameraRef()
{
	return arcBallCamera;
}

glm::mat4 CameraManager::getProjectionMatrix() const
{
	return projectionMatrix;
}

glm::mat4 CameraManager::getViewMatrix() const
{
	return currentCamera->calculateViewMatrix();
}

void CameraManager::calculateProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(45.0f), windowSize.x / windowSize.y, 0.001f, 100000.0f);
}
