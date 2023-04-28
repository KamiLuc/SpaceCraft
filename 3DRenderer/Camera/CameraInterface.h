#pragma once

#include <GL/glew.h>
#include <glm/ext/vector_float3.hpp>
#include "CameraMoveDirection.h"
#include <glm/glm.hpp>

#include <string>

class CameraInterface
{
public:
	CameraInterface(glm::vec3 position, glm::vec3 worldUp, glm::vec3 lookAt,
		GLfloat moveSpeed, GLfloat turnSpeed, const std::string& cameraName = "camera") :
		position(position), worldUp(worldUp), moveSpeed(moveSpeed), turnSpeed(turnSpeed), lookAt(lookAt), cameraName(cameraName) {}

	virtual void updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec) = 0;
	virtual void handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition) = 0;
	virtual void useImmediateGluLookAt() = 0;
	virtual glm::mat4 calculateViewMatrix() const = 0;
	virtual glm::vec3 getPosition() const { return this->position; }

	GLfloat* getMoveSpeedPointer() { return &moveSpeed; }
	GLfloat* getTurnSpeedPointer() { return &turnSpeed; }
	std::string* getCameraNamePointer() { return &cameraName; }

	virtual ~CameraInterface() {}

protected:
	GLfloat moveSpeed;
	GLfloat turnSpeed;
	glm::vec3 position;
	glm::vec3 worldUp;
	glm::vec3 lookAt;
	std::string cameraName;

	virtual void updateCameraProperties() = 0;
};