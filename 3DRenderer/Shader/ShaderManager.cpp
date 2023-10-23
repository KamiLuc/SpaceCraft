#include "ShaderManager.h"

ShaderManager::ShaderManager()
	: shadersCompiled(false)
	, lastUsedShader(nullptr)
{
}

void ShaderManager::loadAndCompileShaders()
{
	checkPath(shadersPath);

	loadCommonCode();
	shadersCompiled.store(false);
	std::vector<std::string> compiledShaders {};

	for (auto& file : std::filesystem::directory_iterator(shadersPath))
	{
		if (file.is_directory())
		{
			continue;
		}

		std::filesystem::path path = file.path();
		std::string fileName = path.stem().string();

		if (std::find(compiledShaders.begin(), compiledShaders.end(), fileName) == compiledShaders.end())
		{
			std::filesystem::path vertexShader = path;
			std::filesystem::path fragmentShader = path;

			vertexShader.replace_extension(".vertex");
			fragmentShader.replace_extension(".fragment");

			try
			{
				auto shader = std::make_shared<Shader>();

				auto vertexShaderCode = readFile(vertexShader);
				auto fragmentShaderCode = readFile(fragmentShader);

				if (vertexShaderCode == std::nullopt)
				{
					throwError(std::vector<std::string>{"readFile returned null from", vertexShader.string()});
				}
				else if (fragmentShaderCode == std::nullopt)
				{
					throwError(std::vector<std::string>{"readFile returned null from", fragmentShader.string()});
				}

				includeCommonCode(*vertexShaderCode);
				includeCommonCode(*fragmentShaderCode);

				shader->createFromString(vertexShaderCode->c_str(), fragmentShaderCode->c_str());
				shaders[fileName] = std::move(shader);
				compiledShaders.emplace_back(std::move(fileName));
			}
			catch (...)
			{
				continue;
			}
		}
	}

	shadersCompiled.store(true);
}

void ShaderManager::setShadersPath(const std::filesystem::path& shadersPath)
{
	this->shadersPath = shadersPath;
}

void ShaderManager::setIncludePath(const std::filesystem::path& commonCodePath)
{
	this->includePath = commonCodePath;
}

void ShaderManager::setLastUsedShader(std::shared_ptr<Shader> lastUsedShader)
{
	this->lastUsedShader = lastUsedShader;
}

void ShaderManager::checkPath(const std::filesystem::path& shadersPath) const
{
	if (!std::filesystem::exists(shadersPath))
	{
		throwError(std::vector<std::string>{"Failed to open ", shadersPath.string(), "Folder doesn't exists"});
	}
}

std::shared_ptr<Shader> ShaderManager::useShader(const std::string& shader)
{
	if (!shaders.contains(shader))
	{
		throwError(std::vector<std::string>{"Shader not exists", "shader"});
	}

	auto& ret = shaders[shader];
	if (ret != lastUsedShader)
	{
		ret->useShader();
		lastUsedShader = ret;
	}
	return ret;
}

std::optional<std::string> ShaderManager::readFile(const std::filesystem::path & filePath) const
{
	std::string fileContent {};
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open())
	{
		printf("Failed to read %s File doesn't exist\n", filePath.string().c_str());
		return std::nullopt;
	}

	std::string line {};
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		fileContent.append(line + "\n");
	}

	fileStream.close();
	return fileContent;
}

void ShaderManager::loadCommonCode()
{
	checkPath(includePath);

	for (auto& file : std::filesystem::directory_iterator(includePath))
	{
		if (file.is_directory())
		{
			continue;
		}

		auto code = readFile(file);
		if (code == std::nullopt)
		{
			throwError(std::vector<std::string>{"readFile returned null"});
		}

		commonCode[file.path().stem().string()] = *code;
	}
}

void ShaderManager::includeCommonCode(std::string& code)
{
	size_t pos = 0;

	while ((pos = code.find("#include \"", pos)) != std::string::npos)
	{
		size_t start = pos;
		pos += 10;

		size_t end = code.find("\"", pos);
		if (end == std::string::npos)
		{
			throwError(std::vector<std::string>{"Can't find closing '\"'"});
		}

		std::string includePath = code.substr(pos, end - pos);
		std::string replacement = commonCode[includePath];

		if (replacement.empty())
		{
			throwError(std::vector<std::string>{"Can't include: ", includePath});
		}

		code.replace(start, end - start + 1, replacement);
	}
}

void ShaderManager::throwError(const std::vector<std::string>& messages) const
{
	std::string exceptionMessage { std::move(std::string(__func__).append(" ")) };

	for (const auto& el : messages)
	{
		exceptionMessage.append(el);
	}

	printf(exceptionMessage.c_str());
	throw std::exception(exceptionMessage.c_str());
}

bool ShaderManager::areShadersCompiled() const
{
	return shadersCompiled.load();
}
