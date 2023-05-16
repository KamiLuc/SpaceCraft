#include "Texture.h"

Texture::Texture(std::filesystem::path fileLocation) : textureID(0), width(0), height(0), bitDepth(0), fileLocation(fileLocation)
{
	if (!std::filesystem::exists(fileLocation)) {
		std::string exceptionMessage{ std::move(std::string(__func__).append(" File doesn't exists: ").append(fileLocation.string().append("\n"))) };
		printf(exceptionMessage.c_str());
		throw std::invalid_argument(exceptionMessage);
	}
}

Texture::~Texture()
{
}

void Texture::loadTexture()
{
	unsigned char* textureData = stbi_load(this->fileLocation.string().c_str(), &this->width, &this->height, &this->bitDepth, 0);

	auto fileExtension = this->fileLocation.extension().string();

	if (fileExtension != ".jpg" && fileExtension != ".png")
	{
		stbi_image_free(textureData);
		return;
	}

	if (!textureData) {
		std::string exceptionMessage{ std::move(std::string(__func__).append(" File is not an image: ").append(fileLocation.string().append("\n"))) };
		printf(exceptionMessage.c_str());
		throw std::runtime_error(exceptionMessage);
	}

	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (fileExtension == ".jpg")
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else if (fileExtension == ".png")
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(textureData);
}

void Texture::useTexture() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
}

void Texture::clearTexture()
{
	glDeleteTextures(1, &this->textureID);
	this->textureID = 0;
	this->width = 0;
	this->height = 0;
	this->bitDepth = 0;
	this->fileLocation = "";
}
