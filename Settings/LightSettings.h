#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace Settings {

	struct LightSettings {
		glm::vec3 color;
		GLfloat ambientIntensity;
		GLfloat diffuseIntensity;
		glm::vec3 direction;

		LightSettings(glm::vec3 color, GLfloat ambientIntensity,
			GLfloat diffuseIntensity, const glm::vec3& direction)
			: color(color), ambientIntensity(ambientIntensity), diffuseIntensity(diffuseIntensity), direction(direction) {}

		LightSettings() : LightSettings({ 1.0f, 1.0f, 1.0f }, 1.0f, 0.0f, { 0.0f, 0.0f, 0.0f }) {}
	};
}