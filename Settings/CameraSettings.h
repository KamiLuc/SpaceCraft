#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>

namespace Settings {

	struct CameraSettings {
		GLfloat moveSpeed;
		GLfloat turnSpeed;
		GLfloat pitch;
		GLfloat yaw;
		glm::vec3 lookAt;
		glm::vec3 position;
		glm::vec3 worldUp;
		std::string cameraName;

		CameraSettings(GLfloat moveSpeed, GLfloat turnSpeed, GLfloat pitch, GLfloat yaw,
					   glm::vec3 position, glm::vec3 lookAt, glm::vec3 worldUp, std::string cameraName)
			: moveSpeed(moveSpeed)
			, turnSpeed(turnSpeed)
			, pitch(pitch)
			, yaw(yaw)
			, position(position)
			, lookAt(lookAt)
			, worldUp(worldUp)
			, cameraName(cameraName)
		{
		}

		CameraSettings() : CameraSettings(0.5f, 0.5f, 0.0f, 0.0f,
										  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
										  "Camera")
		{
		}
	};
}