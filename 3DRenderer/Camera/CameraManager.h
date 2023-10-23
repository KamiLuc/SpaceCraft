#pragma once

#include "FPCamera.h"
#include "ArcBallCamera.h"
#include "CameraMoveDirection.h"
#include "3DRenderer/Shader/UniformLocations.h"
#include "Settings/Settings.h"

#include <list>
#include <string>

class CameraManager
{
public:
	CameraManager(const Settings::CameraSettings& arcBallCameraSettings,
				  const Settings::CameraSettings& firstPersonCameraSettings, const glm::vec2& windowSize);

	void addCameraMoveDirection(const CameraMoveDirection& direction);
	void removeCameraMoveDirection(const CameraMoveDirection& direction);
	void mouseControl(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition);
	void updateCameraPosition(const GLfloat& timeInSec);
	void changeCamera();
	void observePoint(const glm::vec3& point);

	FPCamera& getFirstPersonCameraRef();
	ArcBallCamera& getArcBallCameraRef();
	CameraInterface* getCurrentCamera();
	glm::vec2 getWindowSize() const;

private:
	CameraInterface* currentCamera;
	FPCamera fpCamera;
	ArcBallCamera arcBallCamera;
	std::list<CameraMoveDirection> cameraMoveDirections;
	glm::vec2 windowSize;

	glm::mat4 calculateProjectionMatrix();
};

