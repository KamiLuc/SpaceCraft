#pragma once

#include "Interfaces/Planet.h"
#include "TexturedSphere.h"

class TexturedPlanet : public Planet, public TexturedSphere
{
public:
	TexturedPlanet(const glm::vec<3, Measure>& position, const glm::vec<3, Measure>& velocity, const Measure& mass,
		float scale, const std::string& identifier, const Shader& shader, const Texture& texture);

	virtual void render(const UniformLocations& uniformLocations) const override;
	virtual bool editViaImGui();

private:
};

#pragma once
