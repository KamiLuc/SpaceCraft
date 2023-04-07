#pragma once

#include "CameraInterface.h"
#include <glm/vector_relational.hpp>

#include <glm/gtx/quaternion.hpp>

class ArcBallCamera :public CameraInterface
{
public:
	ArcBallCamera(GLfloat distance, glm::vec3 worldUp, GLfloat moveSpeed, GLfloat turnSpeed);

	virtual void updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec) override;
	virtual void handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition) override;
	virtual glm::mat4 calculateViewMatrix() const override;

private:
	glm::quat rotation;
	glm::vec3 position;
	glm::vec3 up;
	GLfloat distance;

	virtual void updateCameraProperties() override;
};

