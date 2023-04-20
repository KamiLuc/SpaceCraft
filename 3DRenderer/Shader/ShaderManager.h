#pragma once

#include <filesystem>
#include <map>
#include <optional>

#include "Shader.h"

class ShaderManager
{
public:
	ShaderManager(const std::filesystem::path& shadersPath);

	void loadAndCompileShaders();
	void useShader(const std::shared_ptr<Shader> shader);
	void endDrawLoop();

	std::shared_ptr<Shader> getShader(const std::string& shader);
	bool areShadersCompiled() const;

private:
	std::filesystem::path shadersPath;
	std::map<std::string, std::shared_ptr<Shader>> shaders;
	std::atomic<bool> shadersCompiled;
	std::shared_ptr<Shader> lastUsedShader;
};


