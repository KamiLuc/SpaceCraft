#pragma once

#include "Shader.h"

#include <filesystem>
#include <map>
#include <optional>

class ShaderManager
{
public:
	ShaderManager();

	void loadAndCompileShaders();
	void setPath(const std::filesystem::path& shadersPath);
	void setLastUsedShader(std::shared_ptr<Shader> lastUsedShader);
	bool areShadersCompiled() const;
	std::shared_ptr<Shader> useShader(const std::string& shader);

private:
	std::map<std::string, std::shared_ptr<Shader>> shaders;
	std::atomic<bool> shadersCompiled;
	std::filesystem::path shadersPath;
	std::shared_ptr<Shader> lastUsedShader;

	void checkPath(const std::filesystem::path& shadersPath);
};


