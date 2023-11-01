#pragma once

#include "GL/glew.h"
#include "Submodules/stb/stb_image.h"

#include <cstdint>
#include <filesystem>

class Texture
{
public:
	Texture(const std::string& name);
	virtual ~Texture();

	void loadTexture(const std::filesystem::path& fileLocation);
	void useTexture() const;
	void clearTexture();
	std::string getName() const;
	GLuint getTextureId() const;

private:
	GLuint textureID;
	int32_t width;
	int32_t height;
	int32_t bitDepth;
	const std::string name;
};

