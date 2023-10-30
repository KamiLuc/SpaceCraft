#pragma once

#include "AppFramework/Serializer/Serializable.h"

#include <GL\glew.h>

class Material : public Serializable
{
public:
	Material();
	Material(GLfloat intensity, GLfloat shine);

	GLfloat getSpecularIntensity() const { return specularIntensity; }
	GLfloat getShininess() const { return shininess; }

	GLfloat* getSpecularIntensityPtr() { return &specularIntensity; }
	GLfloat* getShininessPtr() { return &shininess; }

	void setSpecularIntensity(GLfloat specularIntensity) { this->specularIntensity = specularIntensity; }
	void setSpecularShininess(GLfloat setSpecularShininess) { this->specularIntensity = specularIntensity; }
	void serialize(boost::archive::text_oarchive & outputArchive, const unsigned int version) override;
	void serialize(boost::archive::text_iarchive & inputArchive, const unsigned int version) override;

private:
	GLfloat specularIntensity;
	GLfloat shininess;
};

