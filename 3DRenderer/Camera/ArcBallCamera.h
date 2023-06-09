#pragma once

#include "CameraInterface.h"
#include "../../Interfaces/EditableViaImGui.h"

#include <algorithm>
#include <glm/vector_relational.hpp>
#include <glm/gtx/quaternion.hpp>

class ArcBallCamera :public CameraInterface, public EditableViaImGui
{
public:
	ArcBallCamera(const Settings::CameraSettings& settings, const glm::vec2& windowSize);

	virtual void updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec) override;
	virtual void handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition) override;
	virtual glm::mat4 calculateViewMatrix() const override;
	void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID) override;

	void useImmediateGluLookAt() override;
	virtual void updateCameraProperties() override;

	glm::vec3 getViewDirection() const;
	glm::vec3 getRightVector() const;

private:

	glm::mat4 viewMatrix;
	glm::vec2 windowSize;
};
