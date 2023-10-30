#pragma once

#include "FPCamera.h"
#include "ArcBallCamera.h"
#include "Settings/Settings.h"
#include "AppFramework/GUI/ObjectEditor.h"

#include <list>
#include <string>

class CameraManager
{
public:
	CameraManager(const Settings::CameraSettings& arcBallCameraSettings,
				  const Settings::CameraSettings& firstPersonCameraSettings, const glm::vec2& windowSize);

	void changeCamera();
	void drawEditors();
	void observePoint(const glm::vec3& point);
	void updateCameraPosition(const GLfloat& timeInSec);
	void addCameraMoveDirection(const CameraMoveDirection& direction);
	void removeCameraMoveDirection(const CameraMoveDirection& direction);
	void mouseControl(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition);
	FPCamera& getFirstPersonCameraRef();
	ArcBallCamera& getArcBallCameraRef();
	CameraInterface* getCurrentCamera();
	glm::vec2 getWindowSize() const;

private:
	ObjectEditor arcBallCameraEditor;
	ObjectEditor fpCameraEditor;
	CameraInterface* currentCamera;
	FPCamera fpCamera;
	ArcBallCamera arcBallCamera;
	std::list<CameraMoveDirection> cameraMoveDirections;
	glm::vec2 windowSize;

	glm::mat4 calculateProjectionMatrix();
};

