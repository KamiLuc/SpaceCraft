#pragma once

#include <GL/glew.h>

struct UniformLocations {
	GLuint uniformProjection;
	GLuint uniformModel;
	GLuint uniformView;
	GLuint uniformAmbientIntensity;
	GLuint uniformAmbientColor;
	GLuint uniformDiffuseIntensity;
	GLuint uniformLightDirection;
	GLuint uniformCameraPosition;
	GLuint uniformSpecularIntensity;
	GLuint uniformShininess;
	GLuint uniformWorldScale;

	UniformLocations();
	void clear();
};