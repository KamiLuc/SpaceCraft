#include "Material.h"

Material::Material()
	: Material(0.0f, 0.0f)
{
}

Material::Material(GLfloat intensity, GLfloat shine)
	: specularIntensity(intensity), shininess(shine)
{
}

void Material::serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version)
{
	outputArchive & shininess;
	outputArchive & specularIntensity;
}

void Material::serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version)
{
	inputArchive & shininess;
	inputArchive & specularIntensity;
}
