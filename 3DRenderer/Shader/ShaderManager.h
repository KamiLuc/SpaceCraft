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
	void setShadersPath(const std::filesystem::path& shadersPath);
	void setIncludePath(const std::filesystem::path& includePath);
	void setLastUsedShader(std::shared_ptr<Shader> lastUsedShader);
	bool areShadersCompiled() const;
	std::shared_ptr<Shader> useShader(const std::string& shader);

private:
	std::optional<std::string> readFile(const std::filesystem::path& filePath) const;
	void loadCommonCode();
	void includeCommonCode(std::string& code);
	void throwError(const std::vector<std::string>& messages) const;

	std::map<std::string, std::shared_ptr<Shader>> shaders;
	std::map<std::string, std::string> commonCode;
	std::atomic<bool> shadersCompiled;
	std::filesystem::path shadersPath;
	std::filesystem::path includePath;
	std::shared_ptr<Shader> lastUsedShader;

	void checkPath(const std::filesystem::path& path) const;
};


