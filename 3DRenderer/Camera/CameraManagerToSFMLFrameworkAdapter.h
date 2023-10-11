#pragma once

#include "CameraManager.h"
#include "AppFramework/EventManager/EventDetails.h"

#include <SFML/Graphics/RenderWindow.hpp>

class CameraManagerToSFMLFrameworkAdapter : public CameraManager
{
public:
	CameraManagerToSFMLFrameworkAdapter(const Settings::CameraSettings& arcBallCameraSettings,
										const Settings::CameraSettings& firstPersonCameraSettings, sf::Window* window);

	void handleKeyboardInput(EventDetails* e);
	void updateCameraPosition(const GLfloat& timeInSec);
	void enableMouseCameraMove(EventDetails* e);
	void disableMouseCameraMove(EventDetails* e);
	void changeCamera(EventDetails* e);

private:
	bool mouseCameraMove;
	sf::Vector2i lastMousePos;
	sf::Window* window;
};