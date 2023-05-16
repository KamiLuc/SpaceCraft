#pragma once

#include <filesystem>
#include <map>
#include <optional>

#include "Shader.h"

class ShaderManager
{
public:
	ShaderManager();

	void loadAndCompileShaders();
	void setPath(const std::filesystem::path& shadersPath);

	std::shared_ptr<Shader> getShader(const std::string& shader);
	bool areShadersCompiled() const;

private:
	std::map<std::string, std::shared_ptr<Shader>> shaders;
	std::atomic<bool> shadersCompiled;
	std::filesystem::path shadersPath;

	void checkPath(const std::filesystem::path& shadersPath);
};


