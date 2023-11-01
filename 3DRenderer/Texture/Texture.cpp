#include "Texture.h"

Texture::Texture(const std::string& name)
	: textureID(0)
	, width(0)
	, height(0)
	, bitDepth(0)
	, name(name)
{
}

Texture::~Texture()
{
	clearTexture();
}

void Texture::loadTexture(const std::filesystem::path& fileLocation)
{
	unsigned char* textureData = stbi_load(fileLocation.string().c_str(), &width, &height, &bitDepth, 0);

	auto fileExtension = fileLocation.extension().string();

	if (fileExtension != ".jpg" && fileExtension != ".png")
	{
		stbi_image_free(textureData);
		return;
	}

	if (!textureData)
	{
		std::string exceptionMessage { std::move(std::string(__func__).append(" File is not an image: ").append(fileLocation.string().append("\n"))) };
		printf(exceptionMessage.c_str());
		throw std::runtime_error(exceptionMessage);
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (fileExtension == ".jpg")
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else if (fileExtension == ".png")
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(textureData);
}

void Texture::useTexture() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::clearTexture()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
}

std::string Texture::getName() const
{
	return name;
}

GLuint Texture::getTextureId() const
{
	return textureID;
}

