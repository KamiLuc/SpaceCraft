#pragma once

#include "FPCamera.h"
#include "ArcBallCamera.h"
#include "CameraMoveDirection.h"

#include <list>

class CameraManager
{
public:
	CameraManager(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed, glm::vec2 windowSize);

	void addCameraMoveDirection(const CameraMoveDirection& direction);
	void removeCameraMoveDirection(const CameraMoveDirection& direction);

	void mouseControl(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition);
	void updateCameraPosition(const GLfloat& timeInSec);
	void useCamera(GLuint uniformView, GLuint uniformEyePosition, GLuint uniformProjection);
	void changeCamera();
	void drawAxis();

private:

	CameraInterface* currentCamera;
	FPCamera fpCamera;
	ArcBallCamera arcBallCamera;

	std::list<CameraMoveDirection> cameraMoveDirections;
	glm::mat4 projectionMatrix;
	glm::vec2 windowSize;

	void calculateProjectionMatrix();
};

