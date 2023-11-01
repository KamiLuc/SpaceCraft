#pragma once

#include "CubeMapTexture.h"
#include "Texture.h"

#include <filesystem>
#include <map>

class Texture;
class CubeMapTexture;

class TextureManager
{
public:
	TextureManager();

	void loadTextures();
	void loadTexturesAsync();
	void setTexturesPath(const std::filesystem::path& texturesPath);
	void setSkyboxTexturesPath(const std::filesystem::path& skyboxPath);
	std::shared_ptr<Texture> getTexture(std::string texture) const;
	std::shared_ptr<CubeMapTexture> getSkyboxTexture() const;
	std::vector<std::string> getTexturesNames() const;
	bool areTexturesLoaded() const;

private:
	std::map<std::string, std::shared_ptr<Texture>> textures;
	std::shared_ptr<CubeMapTexture> skyboxTexture;
	std::atomic<bool> texturesLoaded;
	std::filesystem::path texturesPath;
	std::filesystem::path skyboxTexturesPath;

	void loadSkybox();
	void checkPath(const std::filesystem::path& texturesPath);
};

