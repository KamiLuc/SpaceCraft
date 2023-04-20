#pragma once

#include "CameraInterface.h"

class FPCamera : public CameraInterface
{
public:
	FPCamera(glm::vec3 position, glm::vec3 worldUp, glm::vec3 lookAt, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed);

	virtual void handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition) override;
	virtual void updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec) override;
	virtual glm::mat4 calculateViewMatrix() const override;
	void useImmediateGluLookAt() override;

private:
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	GLfloat yaw;
	GLfloat pitch;

	virtual void updateCameraProperties() override;
};


