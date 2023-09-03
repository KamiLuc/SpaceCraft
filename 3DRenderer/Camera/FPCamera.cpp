#include "FPCamera.h"
#include <glm/ext/matrix_transform.hpp>

FPCamera::FPCamera(const Settings::CameraSettings& settings)
	: CameraInterface(settings)
{
	updateCameraProperties();
}


void FPCamera::updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec)
{
	auto velocity = timeInSec * moveSpeed;

	switch (direction)
	{
		case(CameraMoveDirection::Forward):
			position += front * velocity;
			break;
		case(CameraMoveDirection::Backward):
			position -= front * velocity;
			break;
		case(CameraMoveDirection::Left):
			position -= right * velocity;
			break;
		case(CameraMoveDirection::Right):
			position += right * velocity;
			break;
		default:
			break;
	}
	updateCameraProperties();
}

void FPCamera::handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition)
{
	auto change = newMousePosition - oldMousePosition;
	auto xChange = change.x * turnSpeed;
	auto yChange = change.y * turnSpeed;

	yaw += xChange;
	pitch -= yChange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	updateCameraProperties();
}

void FPCamera::updateCameraProperties()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 FPCamera::calculateViewMatrix() const
{
	return glm::lookAt(position, position + front, up);
}

void FPCamera::editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui)
{
	if (beginImGui)
	{
		ImGui::Begin(("Edit " + cameraName + " " + std::to_string(windowID)).c_str());
	}

	ImGui::DragFloat("Move speed", &moveSpeed, 1.0f, 0.0f, 10000.0f);
	ImGui::DragFloat("Turn speed", &turnSpeed, 0.01f, 0.0f, 10000.0f);;

	if (ImGui::Button("Close", { ImGui::GetWindowWidth(), 20 }))
	{
		objectHandler.removeObjectFromEdit(this);
	}

	if (beginImGui)
	{
		ImGui::End();
	}
}

void FPCamera::useImmediateGluLookAt()
{
	auto center = position + front;
	gluLookAt(position.x, position.y, position.z,
			  center.x, center.y, center.z,
			  worldUp.x, worldUp.y, worldUp.y);
}
