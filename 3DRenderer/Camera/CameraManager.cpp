#include "CameraManager.h"

CameraManager::CameraManager(const Settings::CameraSettings& arcBallCameraSettings, const Settings::CameraSettings& firstPersonCameraSettings, const glm::vec2& windowSize)
	: fpCamera(firstPersonCameraSettings), arcBallCamera(arcBallCameraSettings, windowSize),
	windowSize(windowSize), currentCamera(&arcBallCamera)
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

void CameraManager::mouseControl(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition)
{
	this->currentCamera->handleMouse(oldMousePosition, newMousePosition);
}

void CameraManager::updateCameraPosition(const GLfloat& timeInSec)
{
	for (const auto& it : this->cameraMoveDirections)
	{
		this->currentCamera->updateCameraPosition(it, timeInSec);
	}
}

void CameraManager::useCamera(GLuint uniformView, GLuint uniformEyePosition, GLuint uniformProjection)
{
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(this->currentCamera->calculateViewMatrix()));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));
	auto cPos = this->currentCamera->getPosition();
	glUniform3f(uniformEyePosition, cPos.x, cPos.y, cPos.z);
}

void CameraManager::changeCamera()
{
	if (!ImGui::GetIO().WantCaptureKeyboard) {
		if (this->currentCamera == &this->arcBallCamera)
		{
			this->currentCamera = &this->fpCamera;
		}
		else
		{
			this->currentCamera = &this->arcBallCamera;
		}
	}
}

void CameraManager::observePoint(const glm::vec3& point, const GLfloat& distance)
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

void CameraManager::calculateProjectionMatrix()
{
	this->projectionMatrix = glm::perspective(glm::radians(45.0f), this->windowSize.x / this->windowSize.y, 0.001f, 100000.0f);
}
