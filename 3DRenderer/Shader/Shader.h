#pragma once

#include "UniformLocations.h"

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

	const UniformLocations& getUniformLocations() const;

	void useShader() const;
	void clearShader();

private:
	GLuint shaderID;
	UniformLocations uniformLocations;

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint programID, const char* shaderCode, GLenum shaderType);
};

