#include "Material.h"

Material::Material() : Material(0.0f, 0.0f)
{
}

Material::Material(GLfloat intensity, GLfloat shine) : specularIntensity(intensity), shininess(shine)
{
}

Material::~Material()
{
}

void Material::useMaterial(GLuint specularIntensityLocation, GLuint shininessLocation) const
{
	glUniform1f(specularIntensityLocation, this->specularIntensity);
	glUniform1f(shininessLocation, this->shininess);
}
