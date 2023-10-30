#pragma once

#include "GL/glew.h"
#include "Submodules/stb/stb_image.h"
#include "TextureManager.h"

#include <cstdint>
#include <filesystem>

class TextureManager;

class Texture
{
public:
	Texture(const std::string& name, const TextureManager& textureManager);
	virtual ~Texture();

	void loadTexture(const std::filesystem::path& fileLocation);
	void useTexture() const;
	void clearTexture();
	const TextureManager& getTextureManager() const;
	std::string getName() const;
	GLuint getTextureId() const;

private:
	GLuint textureID;
	int32_t width;
	int32_t height;
	int32_t bitDepth;
	const TextureManager& textureManager;
	const std::string name;
};

