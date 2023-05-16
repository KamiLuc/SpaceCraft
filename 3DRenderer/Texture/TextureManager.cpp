#include "TextureManager.h"

TextureManager::TextureManager() : texturesLoaded(false), texturesPath("")
{
}

void TextureManager::loadTextures()
{
	checkPath(texturesPath);

	texturesLoaded.store(false);
	std::vector<std::string> texturesAlreadyLoaded{};

	for (auto& file : std::filesystem::directory_iterator(texturesPath)) {
		std::filesystem::path path = file.path();
		std::string fileExtension = path.extension().string();
		std::string fileName = path.stem().string();

		if (std::find(texturesAlreadyLoaded.begin(), texturesAlreadyLoaded.end(), fileName) == texturesAlreadyLoaded.end()) {

			try {
				auto texture = std::make_shared<Texture>(path);
				texture->loadTexture();
				textures[fileName] = std::move(texture);
				texturesAlreadyLoaded.emplace_back(std::move(fileName));
			}
			catch (...) {
				continue;
			}
		}
	}

	texturesLoaded.store(true);
}

void TextureManager::loadTexturesAsync()
{
	std::thread loadingThread([&]() {
		loadTextures();
		});

	loadingThread.detach();
}

void TextureManager::setPath(const std::filesystem::path& texturesPath)
{
	this->texturesPath = texturesPath;
}

std::shared_ptr<Texture> TextureManager::getTexture(const std::string& texture)
{
	if (textures.contains(texture)) {
		return textures[texture];
	}
	else {
		return nullptr;
	}
}

bool TextureManager::areTexturesLoaded() const
{
	return texturesLoaded.load();
}

void TextureManager::checkPath(const std::filesystem::path& texturesPath)
{
	if (!std::filesystem::exists(texturesPath)) {
		std::string exceptionMessage{ std::move(std::string(__func__).append(" Failed to open ").
			append(texturesPath.string().c_str()).append(" Folder doesn't exist\n")) };
		printf(exceptionMessage.c_str());
		throw std::exception(exceptionMessage.c_str());
	}
}
