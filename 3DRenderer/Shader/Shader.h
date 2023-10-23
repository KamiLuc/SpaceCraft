#pragma once

#include "UniformLocations.h"
#include "3DRenderer/Material.h"
#include "3DRenderer/Camera/CameraInterface.h"
#include "3DRenderer/Light/OmnipresentLight.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader();
	~Shader();

	void createFromString(const char* vertexCode, const char* fragmentCode);
	void useShader() const;
	void clearShader();
	const UniformLocations& getUniformLocations() const;

	void useModel(const glm::mat4& model) const;
	void useMaterial(const Material& material) const;
	void useCamera(const CameraInterface& camera) const;
	void useOmnipresentLight(const OmnipresentLight& omnipresentLight) const;

	template<typename Container>
	void usePointLights(const Container& container) const;

private:
	unsigned int pointLightCount;
	GLuint shaderID;
	UniformLocations uniformLocations;

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint programID, const char* shaderCode, GLenum shaderType);
};

template<typename Container>
inline void Shader::usePointLights(const Container& container) const
{
	glUniform1i(uniformLocations.pointLightCount, static_cast<unsigned int>(container.size()));

	for (size_t i = 0; i < container.size(); ++i)
	{
		auto it = container.begin();
		std::advance(it, i);
		(*it)->useLight(uniformLocations.pointLights[i]);
	}
}
