#pragma once

#include "CameraInterface.h"

class FPCamera : public CameraInterface
{
public:
	FPCamera(const Settings::CameraSettings& settings);

	virtual void handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition) override;
	virtual void updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec) override;
	virtual glm::mat4 calculateViewMatrix() const override;
	void useImmediateGluLookAt() override;

private:
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	virtual void updateCameraProperties() override;
};


