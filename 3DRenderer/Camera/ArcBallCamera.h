#pragma once

#include "CameraInterface.h"
#include "AppFramework/GUI/EditableViaGui.h"

#include <cmath>
#include <algorithm>
#include <glm/vector_relational.hpp>
#include <glm/gtx/quaternion.hpp>

class ArcBallCamera : public CameraInterface, public EditableViaGui
{
public:
	ArcBallCamera(const Settings::CameraSettings& settings, const glm::vec2& windowSize);

	glm::vec3 getViewDirection() const;
	glm::vec3 getRightVector() const;
	glm::mat4 getViewMatrix() const override;
	void editViaGui() override;
	void useImmediateGluLookAt() override;
	void updateCameraProperties() override;
	void handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition) override;
	void updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec) override;

private:
	glm::mat4 viewMatrix;
	glm::vec2 windowSize;
};
