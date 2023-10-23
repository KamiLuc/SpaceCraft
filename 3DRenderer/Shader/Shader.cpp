#include "Shader.h"

Shader::Shader()
	: shaderID(0)
	, pointLightCount(0)
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

const UniformLocations& Shader::getUniformLocations() const
{
	return uniformLocations;
}

void Shader::useModel(const glm::mat4& model) const
{
	glUniformMatrix4fv(uniformLocations.model, 1, GL_FALSE, glm::value_ptr(model));
}

void Shader::useMaterial(const Material& material) const
{
	glUniform1f(uniformLocations.material.specularIntensity, material.getSpecularIntensity());
	glUniform1f(uniformLocations.material.shininess, material.getShininess());
}

void Shader::useCamera(const CameraInterface& camera) const
{
	glUniformMatrix4fv(uniformLocations.camera.view, 1, GL_FALSE, glm::value_ptr(camera.getViewMatrix()));
	glUniformMatrix4fv(uniformLocations.camera.projection, 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix()));
	auto cPos = camera.getPosition();
	glUniform3f(uniformLocations.camera.position, cPos.x, cPos.y, cPos.z);
}

void Shader::useOmnipresentLight(const OmnipresentLight& omnipresentLight) const
{
	auto color = omnipresentLight.getColor();
	glUniform3f(uniformLocations.omnipresentLight.color, color.r, color.g, color.b);
	glUniform1f(uniformLocations.omnipresentLight.ambientIntensity, omnipresentLight.getAmbientIntensity());
}

void Shader::useShader() const
{
	glUseProgram(this->shaderID);
}

void Shader::clearShader()
{
	if (this->shaderID != 0)
	{
		glDeleteProgram(this->shaderID);
		this->shaderID = 0;
	}

	uniformLocations.clear();
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (shaderID == 0)
	{
		printf("Error creating shader program!\n");
		return;
	}

	addShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
		printf("Error linking program: %s\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
		printf("Error validating program: %s\n", eLog);
		return;
	}

	uniformLocations.model = glGetUniformLocation(shaderID, "model");
	uniformLocations.camera.projection = glGetUniformLocation(shaderID, "projection");
	uniformLocations.camera.view = glGetUniformLocation(shaderID, "view");
	uniformLocations.camera.position = glGetUniformLocation(shaderID, "cameraPosition");
	uniformLocations.omnipresentLight.color = glGetUniformLocation(shaderID, "omnipresentLight.color");
	uniformLocations.omnipresentLight.ambientIntensity = glGetUniformLocation(shaderID, "omnipresentLight.ambientIntensity");
	uniformLocations.material.specularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
	uniformLocations.material.shininess = glGetUniformLocation(shaderID, "material.shininess");
	uniformLocations.orbitColor = glGetUniformLocation(shaderID, "orbitColor");
	uniformLocations.pointLightCount = glGetUniformLocation(shaderID, "pointLightCount");

	for (unsigned int i = 0; i < uniformLocations.pointLights.size(); ++i)
	{
		char buffer[100] = { '\0' };
		snprintf(buffer, sizeof(buffer), "pointLights[%d].base.color", i);
		uniformLocations.pointLights[i].color = glGetUniformLocation(shaderID, buffer);

		snprintf(buffer, sizeof(buffer), "pointLights[%d].base.ambientIntensity", i);
		uniformLocations.pointLights[i].ambientIntensity = glGetUniformLocation(shaderID, buffer);

		snprintf(buffer, sizeof(buffer), "pointLights[%d].diffuseIntensity", i);
		uniformLocations.pointLights[i].diffuseIntensity = glGetUniformLocation(shaderID, buffer);

		snprintf(buffer, sizeof(buffer), "pointLights[%d].position", i);
		uniformLocations.pointLights[i].position = glGetUniformLocation(shaderID, buffer);

		snprintf(buffer, sizeof(buffer), "pointLights[%d].constant", i);
		uniformLocations.pointLights[i].constant = glGetUniformLocation(shaderID, buffer);

		snprintf(buffer, sizeof(buffer), "pointLights[%d].linear", i);
		uniformLocations.pointLights[i].linear = glGetUniformLocation(shaderID, buffer);

		snprintf(buffer, sizeof(buffer), "pointLights[%d].exponent", i);
		uniformLocations.pointLights[i].exponent = glGetUniformLocation(shaderID, buffer);
	}
}

void Shader::addShader(GLuint programID, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1] { 0 };
	theCode[0] = shaderCode;

	GLint codeLenght[1] { 0 };
	codeLenght[0] = static_cast<GLint>(strlen(shaderCode));

	glShaderSource(theShader, 1, theCode, codeLenght);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
		printf("Error compiling the %d shader: %s\n", shaderType, eLog);
		return;
	}

	glAttachShader(programID, theShader);
}
