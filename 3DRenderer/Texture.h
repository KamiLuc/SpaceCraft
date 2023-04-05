#pragma once

#include "GL/glew.h"
#include "../stb/stb_image.h"

#include <cstdint>
#include <filesystem>

class Texture
{
public:
	Texture(std::filesystem::path fileLocation);
	~Texture();

	void loadTexture();
	void useTexture();
	void clearTexture();

private:
	GLuint textureID;
	int32_t width;
	int32_t height;
	int32_t bitDepth;
	std::filesystem::path fileLocation;
};

