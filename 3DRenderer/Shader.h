#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();

	void createFromString(const char* vertexCode, const char* fragmentCode);
	void createFromFiles(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentSHaderPath);

	std::optional<std::string> readFile(const std::filesystem::path& filePath);

	GLuint getProjectionLocation() const;
	GLuint getModelLocation() const;
	GLuint getViewLocation() const;
	GLuint getAmbientIntensityLocation() const;
	GLuint getAmbientColorLocation() const;
	GLuint getDiffuseIntensityLocation() const;
	GLuint getLightDirectionLocation() const;
	GLuint getSpecularIntensityLocation() const;
	GLuint getShininessLocation() const;
	GLuint getCameraPositionLocation() const;

	void useShader();
	void clearShader();

private:
	GLuint shaderID;
	GLuint uniformProjection;
	GLuint uniformModel;
	GLuint uniformView;
	GLuint uniformAmbientIntensity;
	GLuint uniformAmbientColor;
	GLuint uniformDiffuseIntensity;
	GLuint uniformLightDirection;
	GLuint uniformCameraPosition;
	GLuint uniformSpecularIntensity;
	GLuint uniformShininess;

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint programID, const char* shaderCode, GLenum shaderType);
};

