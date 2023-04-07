#include "CameraManagerToSFMLFrameworkAdapter.h"

CameraManagerToSFMLFrameworkAdapter::CameraManagerToSFMLFrameworkAdapter(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed, sf::Window* window)
	: CameraManager(position, up, yaw, pitch, moveSpeed, turnSpeed,
		static_cast<GLfloat>(window->getSize().x) / static_cast<GLfloat>(window->getSize().y)),
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

		this->mouseControl(static_cast<GLfloat>(mousePos.x - this->lastMousePos.x), static_cast<GLfloat>(mousePos.y - this->lastMousePos.y));

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
