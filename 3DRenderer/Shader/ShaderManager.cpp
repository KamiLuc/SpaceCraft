#include "ShaderManager.h"

ShaderManager::ShaderManager()
	: shadersCompiled(false)
	, lastUsedShader(nullptr)
{
}

void ShaderManager::loadAndCompileShaders()
{
	checkPath(shadersPath);

	shadersCompiled.store(false);
	std::vector<std::string> compiledShaders{};

	for (auto& file : std::filesystem::directory_iterator(shadersPath)) {
		std::filesystem::path path = file.path();
		std::string fileExtension = path.extension().string();
		std::string fileName = path.stem().string();

		if (std::find(compiledShaders.begin(), compiledShaders.end(), fileName) == compiledShaders.end()) {

			std::filesystem::path vertexShader = path;
			std::filesystem::path fragmentShader = path;

			vertexShader.replace_extension(".vertex");
			fragmentShader.replace_extension(".fragment");

			try {
				auto shader = std::make_shared<Shader>();
				shader->createFromFiles(vertexShader, fragmentShader);

				shaders[fileName] = std::move(shader);
				compiledShaders.emplace_back(std::move(fileName));
			}
			catch (...) {
				continue;
			}
		}
	}

	shadersCompiled.store(true);
}

void ShaderManager::setPath(const std::filesystem::path& shadersPath)
{
	this->shadersPath = shadersPath;
}

void ShaderManager::checkPath(const std::filesystem::path& shadersPath)
{
	if (!std::filesystem::exists(shadersPath)) {
		std::string exceptionMessage{ std::move(std::string(__func__).append(" Failed to open ").
			append(shadersPath.string().c_str()).append(" Folder doesn't exist\n")) };
		printf(exceptionMessage.c_str());
		throw std::exception(exceptionMessage.c_str());
	}
}

std::shared_ptr<Shader> ShaderManager::getShader(const std::string& shader)
{
	if (shaders.contains(shader)) {
		return shaders[shader];
	}
	else {
		return nullptr;
	}
}

bool ShaderManager::areShadersCompiled() const
{
	return shadersCompiled.load();
}
