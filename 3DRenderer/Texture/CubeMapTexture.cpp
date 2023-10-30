#include "CubeMapTexture.h"

CubeMapTexture::CubeMapTexture()
	: textureID(0)
{
}

void CubeMapTexture::loadTexture(const std::vector<std::filesystem::path>& texturesLocation)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width = 0;
	int height = 0;
	int bitDepth = 0;
	unsigned int counter = 0;

	for (auto& path : texturesLocation)
	{
		unsigned char* textureData = stbi_load(path.string().c_str(), &width, &height, &bitDepth, 0);

		auto fileExtension = path.extension().string();

		if (fileExtension == ".jpg")
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + counter, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
		}
		else if (fileExtension == ".png")
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + counter, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(textureData);
		counter++;
	}
}

void CubeMapTexture::useTexture() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}

void CubeMapTexture::clearTexture()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
}
