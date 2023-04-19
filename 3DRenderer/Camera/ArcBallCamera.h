#pragma once

#include "CameraInterface.h"

#include <algorithm>
#include <glm/vector_relational.hpp>
#include <glm/gtx/quaternion.hpp>

class ArcBallCamera :public CameraInterface
{
public:
	ArcBallCamera(GLfloat distance, glm::vec3 worldUp, glm::vec3 lookAt, GLfloat moveSpeed, GLfloat turnSpeed, glm::vec2 windowSize);

	virtual void updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec) override;
	virtual void handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition) override;
	virtual glm::mat4 calculateViewMatrix() const override;

	glm::vec3 getViewDirection() const;
	glm::vec3 getRightVector() const;

private:
	virtual void updateCameraProperties() override;

	glm::mat4 viewMatrix;
	glm::vec2 windowSize;
};
