#include "Shader.h"

Shader::Shader()
	: shaderID(0), uniformModel(-1), uniformProjection(-1), uniformView(-1), uniformAmbientColor(-1), uniformAmbientIntensity(-1), uniformCameraPosition(-1),
	uniformDiffuseIntensity(-1), uniformLightDirection(-1), uniformSpecularIntensity(-1), uniformShininess(-1)
{
}

Shader::~Shader()
{
	this->clearShader();
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode)
{
	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragmentShaderPath)
{
	std::optional<std::string> vertexCode = readFile(vertexShaderPath);
	std::optional<std::string> fragmentCode = readFile(fragmentShaderPath);

	if (vertexCode == std::nullopt) {
		std::string exceptionMessage{ std::move(std::string(__func__).append("readFile returned null from vertexShaderPath")) };
		printf(exceptionMessage.c_str());
		throw std::exception(exceptionMessage.c_str());
	}
	else if (fragmentCode == std::nullopt) {
		std::string exceptionMessage{ std::move(std::string(__func__).append("readFile returned null from fragmentShaderPath")) };
		printf(exceptionMessage.c_str());
		throw std::exception(exceptionMessage.c_str());
	}

	this->compileShader(vertexCode.value().c_str(), fragmentCode.value().c_str());
}

std::optional<std::string> Shader::readFile(const std::filesystem::path& filePath)
{
	std::string fileContent{};
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s File doesn't exist\n", filePath.string().c_str());
		return std::nullopt;
	}

	std::string line{};
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		fileContent.append(line + "\n");
	}

	fileStream.close();
	return fileContent;
}

GLuint Shader::getProjectionLocation() const
{
	return this->uniformProjection;
}

GLuint Shader::getModelLocation() const
{
	return this->uniformModel;
}

GLuint Shader::getViewLocation() const
{
	return this->uniformView;
}

GLuint Shader::getAmbientIntensityLocation() const
{
	return this->uniformAmbientIntensity;
}

GLuint Shader::getAmbientColorLocation() const
{
	return this->uniformAmbientColor;
}

GLuint Shader::getDiffuseIntensityLocation() const
{
	return this->uniformDiffuseIntensity;
}

GLuint Shader::getLightDirectionLocation() const
{
	return this->uniformLightDirection;
}

GLuint Shader::getSpecularIntensityLocation() const
{
	return this->uniformSpecularIntensity;
}

GLuint Shader::getShininessLocation() const
{
	return this->uniformShininess;
}

GLuint Shader::getCameraPositionLocation() const
{
	return this->uniformCameraPosition;
}

void Shader::useShader()
{
	glUseProgram(this->shaderID);
}

void Shader::clearShader()
{
	if (this->shaderID != 0) {
		glDeleteProgram(this->shaderID);
		this->shaderID = 0;
	}

	this->uniformModel = 0;
	this->uniformProjection = 0;
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (shaderID == 0) {
		printf("Error creating shader program!\n");
		return;
	}

	addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
		
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
		printf("Error validating program: %s\n", eLog);
		return;
	}

	this->uniformModel = glGetUniformLocation(shaderID, "model");
	this->uniformProjection = glGetUniformLocation(shaderID, "projection");
	this->uniformView = glGetUniformLocation(shaderID, "view");
	this->uniformAmbientColor = glGetUniformLocation(shaderID, "directionalLight.color");
	this->uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
	this->uniformLightDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
	this->uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.diffuseIntensity");
	this->uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity"); //d on purpose
	this->uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
	this->uniformCameraPosition = glGetUniformLocation(shaderID, "cameraPosition");
}

void Shader::addShader(GLuint programID, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1]{ 0 };
	theCode[0] = shaderCode;

	GLint codeLenght[1]{ 0 };
	codeLenght[0] = static_cast<GLint>(strlen(shaderCode));

	glShaderSource(theShader, 1, theCode, codeLenght);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
		printf("Error compiling the %d shader: %s\n", shaderType, eLog);
		return;
	}

	glAttachShader(programID, theShader);
}
