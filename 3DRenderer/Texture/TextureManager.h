#pragma once

#include <filesystem>
#include <map>

#include "Texture.h"

class TextureManager
{
public:
	TextureManager(const std::filesystem::path& texturesPath);

	void loadTextures();
	void loadTexturesAsync();

	std::shared_ptr<Texture> getTexture(const std::string& texture);
	bool areTexturesLoaded() const;

private:
	std::filesystem::path texturesPath;
	std::map<std::string, std::shared_ptr<Texture>> textures;
	std::atomic<bool> texturesLoaded;
};

