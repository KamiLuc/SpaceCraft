#pragma once

#include "Camera.h"
#include "CameraMoveDirection.h"

#include <list>

class CameraManager
{
public:
	CameraManager(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed);

	void addCameraMoveDirection(const CameraMoveDirection& direction);
	void removeCameraMoveDirection(const CameraMoveDirection& direction);

	void mouseControl(GLfloat xChange, GLfloat yChange);
	void updateCameraPosition(const GLfloat& timeInSec);
	void useCamera(GLuint uniformView, GLuint uniformEyePosition);

protected:
	Camera camera;
	std::list<CameraMoveDirection> cameraMoveDirections;
	GLfloat moveSpeed;
	GLfloat turnSpeed;
};

