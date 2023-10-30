#pragma once

#include "Texture.h"

#include <filesystem>

class CubeMapTexture
{
public:
	CubeMapTexture();

	void loadTexture(const std::vector<std::filesystem::path>& texturesLocation);
	void useTexture() const;
	void clearTexture();

private:
	GLuint textureID;
};

