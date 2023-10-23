#include "CameraManager.h"

#include <glm/gtc/type_ptr.hpp>

CameraManager::CameraManager(const Settings::CameraSettings& arcBallCameraSettings,
							 const Settings::CameraSettings& firstPersonCameraSettings, const glm::vec2& windowSize)
	: windowSize(windowSize)
	, currentCamera(&arcBallCamera)
	, fpCamera(firstPersonCameraSettings)
	, arcBallCamera(arcBallCameraSettings, windowSize)
{
	auto projMat = calculateProjectionMatrix();
	fpCamera.setProjectionMatrix(projMat);
	arcBallCamera.setProjectionMatrix(projMat);
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

CameraInterface * CameraManager::getCurrentCamera()
{
	return currentCamera;
}

glm::vec2 CameraManager::getWindowSize() const
{
	return windowSize;
}

glm::mat4 CameraManager::calculateProjectionMatrix()
{
	return glm::perspective(glm::radians(45.0f), windowSize.x / windowSize.y, 0.001f, 100000.0f);
}
