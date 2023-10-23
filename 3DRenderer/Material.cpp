#include "Material.h"

Material::Material()
	: Material(0.0f, 0.0f)
{
}

Material::Material(GLfloat intensity, GLfloat shine)
	: specularIntensity(intensity), shininess(shine)
{
}

Material::~Material()
{
}
