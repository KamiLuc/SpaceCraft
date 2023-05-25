#pragma once

#include "Interfaces/Planet.h"
#include "Interfaces/Colored.h"
#include "Interfaces/Renderable.h"
#include "ColoredSphere.h"

class ColoredPlanet : public Planet, public ColoredSphere, public Colored
{
public:
	ColoredPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
		float scale, const std::string& identifier, const Shader& shader, const glm::vec4& color);

	virtual void render(const UniformLocations& uniformLocations) const override;
	virtual void editViaImGui(ImGuiEditableObjectsHandler* objectHandler, unsigned int windowID) override;

private:
};

