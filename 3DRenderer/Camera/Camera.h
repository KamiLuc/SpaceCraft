#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Camera
{
public:
	friend class CameraManager;

	Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch);
	~Camera();

	glm::vec3 getPosition() const;

	glm::mat4 calculateViewMatrix() const;

private:
	bool cameraMovmentDisabled;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	GLfloat yaw;
	GLfloat pitch;

	void updateCameraProperties();
};

