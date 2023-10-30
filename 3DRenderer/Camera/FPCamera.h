#pragma once

#include "CameraInterface.h"
#include "AppFramework/GUI/EditableViaGui.h"


class FPCamera : public CameraInterface, public EditableViaGui
{
public:
	FPCamera(const Settings::CameraSettings& settings);

	void handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition) override;
	void updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec) override;
	glm::mat4 getViewMatrix() const override;
	void editViaGui() override;
	void useImmediateGluLookAt() override;

private:
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	void updateCameraProperties() override;
};
