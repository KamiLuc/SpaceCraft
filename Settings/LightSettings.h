#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace Settings {

	struct MainLightSettings {

		glm::vec3 color;
		GLfloat ambientIntensity;

		MainLightSettings(glm::vec3 color, GLfloat ambientIntensity)
			: color(color)
			, ambientIntensity(ambientIntensity)
		{
		}

		MainLightSettings() : MainLightSettings({ 1.0f, 1.0f, 1.0f }, 1.0f) {}
	};
}