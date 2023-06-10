#pragma once

#include "../Interfaces/Planet.h"
#include "../Interfaces/Colored.h"
#include "../Interfaces/Renderable.h"
#include "../3DRenderer/Mesh/ColoredMesh.h"

#include <vector>

class ColoredPlanet : public Planet, public Colored, public Renderable
{
public:
	ColoredPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass, const Measure<1>& radius,
		float scale, const std::string& identifier, const Shader& shader, const glm::vec4& color);

	virtual void render(const UniformLocations& uniformLocations) const override;
	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID) override;
	virtual glm::mat4 getModelMatrix() const override;

private:
	ColoredMesh mesh;
};

