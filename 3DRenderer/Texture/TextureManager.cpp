#include "TextureManager.h"

TextureManager::TextureManager()
	: texturesLoaded(false)
	, texturesPath("")
{
}

void TextureManager::loadTextures()
{
	texturesLoaded.store(false);

	loadSkybox();
	checkPath(texturesPath);

	std::vector<std::string> alreadyLoadedTextures {};
	for (auto& file : std::filesystem::directory_iterator(texturesPath))
	{
		if (file.is_directory())
		{
			continue;
		}

		std::filesystem::path path = file.path();
		std::string fileExtension = path.extension().string();
		std::string fileName = path.stem().string();

		if (std::find(alreadyLoadedTextures.begin(), alreadyLoadedTextures.end(), fileName) == alreadyLoadedTextures.end())
		{
			try
			{
				auto texture = std::make_shared<Texture>(fileName);
				texture->loadTexture(path);
				std::transform(fileName.begin(), fileName.end(), fileName.begin(), toupper);
				textures[fileName] = std::move(texture);
				alreadyLoadedTextures.emplace_back(std::move(fileName));
			}
			catch (std::exception& e)
			{
				printf("%s %s", __func__, e.what());
				continue;
			}
		}
	}

	texturesLoaded.store(true);
}

void TextureManager::loadTexturesAsync()
{
	std::thread loadingThread([&]()
							  {
								  loadTextures();
							  });

	loadingThread.detach();
}

void TextureManager::setTexturesPath(const std::filesystem::path& texturesPath)
{
	this->texturesPath = texturesPath;
}

void TextureManager::setSkyboxTexturesPath(const std::filesystem::path& skyboxPath)
{
	this->skyboxTexturesPath = skyboxPath;
}

std::shared_ptr<Texture> TextureManager::getTexture(std::string texture) const
{
	std::transform(texture.begin(), texture.end(), texture.begin(), toupper);
	if (textures.contains(texture))
	{
		return textures.at(texture);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<CubeMapTexture> TextureManager::getSkyboxTexture() const
{
	return skyboxTexture;
}

bool TextureManager::areTexturesLoaded() const
{
	return texturesLoaded.load();
}

std::vector<std::string> TextureManager::getTexturesNames() const
{
	std::vector<std::string> result {};

	for (const auto& el : textures)
	{
		result.emplace_back(el.first);
	}

	return result;
}

void TextureManager::loadSkybox()
{
	checkPath(skyboxTexturesPath);

	std::vector<std::filesystem::path> skyboxTextures;
	skyboxTextures.resize(6);

	for (const auto& file : std::filesystem::directory_iterator(skyboxTexturesPath))
	{
		auto fileName = file.path().stem().string();

		if (fileName == "right")
		{
			skyboxTextures[0] = file.path();
		}
		else if (fileName == "left")
		{
			skyboxTextures[1] = file.path();
		}
		else if (fileName == "top")
		{
			skyboxTextures[2] = file.path();
		}
		else if (fileName == "bottom")
		{
			skyboxTextures[3] = file.path();
		}
		else if (fileName == "front")
		{
			skyboxTextures[4] = file.path();
		}
		else if (fileName == "back")
		{
			skyboxTextures[5] = file.path();
		}
	}

	try
	{
		skyboxTexture = std::make_shared<CubeMapTexture>();
		skyboxTexture->loadTexture(skyboxTextures);
	}
	catch (...)
	{
	}
}

void TextureManager::checkPath(const std::filesystem::path& texturesPath)
{
	if (!std::filesystem::exists(texturesPath))
	{
		std::string exceptionMessage { std::move(std::string(__func__).append(" Failed to open ").
			append(texturesPath.string().c_str()).append(" Folder doesn't exist\n")) };
		printf(exceptionMessage.c_str());
		throw std::exception(exceptionMessage.c_str());
	}
}
