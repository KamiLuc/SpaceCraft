#include "CameraManagerToSFMLFrameworkAdapter.h"

CameraManagerToSFMLFrameworkAdapter::CameraManagerToSFMLFrameworkAdapter(const Settings::CameraSettings& arcBallCameraSettings,
	const Settings::CameraSettings& firstPersonCameraSettings, sf::Window* window)
	: CameraManager(arcBallCameraSettings, firstPersonCameraSettings,
		{ static_cast<GLfloat>(window->getSize().x), static_cast<GLfloat>(window->getSize().y) }),
	window(window), mouseCameraMove(false), lastMousePos(0, 0)
{
}

void CameraManagerToSFMLFrameworkAdapter::handleKeyboardInput(EventDetails* e)
{
	const auto& name = e->name;

	if (name == "Start_Camera_Forward")
	{
		this->addCameraMoveDirection(CameraMoveDirection::Forward);
	}
	else if (name == "Stop_Camera_Forward")
	{
		this->removeCameraMoveDirection(CameraMoveDirection::Forward);
	}
	else if (name == "Start_Camera_Backward")
	{
		this->addCameraMoveDirection(CameraMoveDirection::Backward);
	}
	else if (name == "Stop_Camera_Backward")
	{
		this->removeCameraMoveDirection(CameraMoveDirection::Backward);
	}
	else if (name == "Start_Camera_Left")
	{
		this->addCameraMoveDirection(CameraMoveDirection::Left);
	}
	else if (name == "Stop_Camera_Left")
	{
		this->removeCameraMoveDirection(CameraMoveDirection::Left);
	}
	else if (name == "Start_Camera_Right")
	{
		this->addCameraMoveDirection(CameraMoveDirection::Right);
	}
	else if (name == "Stop_Camera_Right")
	{
		this->removeCameraMoveDirection(CameraMoveDirection::Right);
	}
}

void CameraManagerToSFMLFrameworkAdapter::updateCameraPosition(const GLfloat& timeInSec)
{
	if (this->mouseCameraMove)
	{
		auto mousePos = sf::Mouse::getPosition(*this->window);

		glm::vec2 oldPos(this->lastMousePos.x, this->lastMousePos.y);
		glm::vec2 newPos(mousePos.x, mousePos.y);

		this->mouseControl(oldPos, newPos);

		this->lastMousePos = mousePos;
	}

	CameraManager::updateCameraPosition(timeInSec);
}

void CameraManagerToSFMLFrameworkAdapter::enableMouseCameraMove(EventDetails* e)
{
	this->mouseCameraMove = true;
	this->lastMousePos.x = e->mouse.x;
	this->lastMousePos.y = e->mouse.y;
}

void CameraManagerToSFMLFrameworkAdapter::disableMouseCameraMove(EventDetails* e)
{
	this->mouseCameraMove = false;
}

void CameraManagerToSFMLFrameworkAdapter::changeCamera(EventDetails* e)
{
	CameraManager::changeCamera();
}
