#pragma once

#include "../Interfaces/RenderablePlanet.h"
#include "../Interfaces/Colored.h"
#include "../3DRenderer/Mesh/ColoredMesh.h"

#include <vector>

class ColoredPlanet : public RenderablePlanet, public Colored
{
public:
	ColoredPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass, const Measure<1>& radius,
		float scale, const std::string& identifier, const Shader& shader, const glm::vec4& color);
	virtual ~ColoredPlanet() {}

	virtual void render(const UniformLocations& uniformLocations) const override;
	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID) override;

private:
	ColoredMesh mesh;
};

