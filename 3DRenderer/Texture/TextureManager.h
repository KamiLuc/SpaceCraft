#pragma once

#include "Texture.h"

#include <filesystem>
#include <map>

class Texture;

class TextureManager
{
public:
	TextureManager();

	void loadTextures();
	void loadTexturesAsync();
	void setPath(const std::filesystem::path& texturesPath);
	std::shared_ptr<Texture> getTexture(const std::string& texture) const;
	std::vector<std::string> getTexturesNames() const;
	bool areTexturesLoaded() const;

private:
	std::map<std::string, std::shared_ptr<Texture>> textures;
	std::atomic<bool> texturesLoaded;
	std::filesystem::path texturesPath;

	void checkPath(const std::filesystem::path& texturesPath);
};

