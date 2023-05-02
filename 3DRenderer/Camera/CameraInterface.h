#pragma once

#include <GL/glew.h>
#include <glm/ext/vector_float3.hpp>
#include <string>
#include <glm/glm.hpp>
#include <stdexcept>

#include "../../Settings/Settings.h"
#include "CameraMoveDirection.h"

class CameraInterface
{
public:
	CameraInterface(Settings::CameraSettings* settings) : settings(settings) {
		if (settings == nullptr) {
			throw std::invalid_argument("settings pointer is null");
		}
	}

	virtual void updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec) = 0;
	virtual void handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition) = 0;
	virtual void useImmediateGluLookAt() = 0;
	virtual glm::mat4 calculateViewMatrix() const = 0;
	virtual glm::vec3 getPosition() const { return settings->position; }

	virtual ~CameraInterface() {}

protected:
	Settings::CameraSettings* settings;

	virtual void updateCameraProperties() = 0;
};