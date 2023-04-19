#pragma once

#include <GL/glew.h>
#include <glm/ext/vector_float3.hpp>
#include "CameraMoveDirection.h"
#include <glm/glm.hpp>

class CameraInterface
{
public:
	CameraInterface(glm::vec3 position, glm::vec3 worldUp, glm::vec3 lookAt, GLfloat moveSpeed, GLfloat turnSpeed) :
		position(position), worldUp(worldUp), moveSpeed(moveSpeed), turnSpeed(turnSpeed), lookAt(lookAt) {}

	virtual void updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec) = 0;
	virtual void handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition) = 0;
	virtual glm::mat4 calculateViewMatrix() const = 0;
	virtual glm::vec3 getPosition() const { return this->position; }

	virtual ~CameraInterface() {}

protected:
	GLfloat moveSpeed;
	GLfloat turnSpeed;
	glm::vec3 position;
	glm::vec3 worldUp;
	glm::vec3 lookAt;

	virtual void updateCameraProperties() = 0;
};