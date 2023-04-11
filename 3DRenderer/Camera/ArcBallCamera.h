#pragma once

#include "CameraInterface.h"

#include <algorithm>
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
	virtual void updateCameraProperties() override;

	glm::vec2 viewport;
	glm::vec3 lookAt;
	glm::mat3 rotation;
	GLfloat distance;
};

