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
	CameraInterface(GLfloat moveSpeed, GLfloat turnSpeed, GLfloat pitch, GLfloat yaw,
		const glm::vec3& lookAt, const glm::vec3& position, const glm::vec3& worldUp, const std::string& name)
		: moveSpeed(moveSpeed)
		, turnSpeed(turnSpeed)
		, pitch(pitch)
		, yaw(yaw)
		, lookAt(lookAt)
		, position(position)
		, worldUp(worldUp)
		, cameraName(name) {}

	CameraInterface(const Settings::CameraSettings& settings)
		: CameraInterface(settings.moveSpeed, settings.turnSpeed, settings.pitch, settings.yaw, settings.lookAt,
			settings.position, settings.worldUp, settings.cameraName) {}

	virtual void updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec) = 0;
	virtual void handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition) = 0;
	virtual void useImmediateGluLookAt() = 0;
	virtual glm::mat4 calculateViewMatrix() const = 0;

	glm::vec3 getPosition() const { return position; }
	void setLookAt(const glm::vec3& lookAt) { this->lookAt = lookAt; }
	void setCameraPosition(const glm::vec3& position) { this->position = position; }

	virtual ~CameraInterface() {}

protected:
	GLfloat moveSpeed;
	GLfloat turnSpeed;
	GLfloat pitch;
	GLfloat yaw;
	glm::vec3 lookAt;
	glm::vec3 position;
	glm::vec3 worldUp;
	std::string cameraName;

	virtual void updateCameraProperties() = 0;
};