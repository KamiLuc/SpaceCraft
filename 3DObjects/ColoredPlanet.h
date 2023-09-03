#pragma once

#include "../Interfaces/RenderablePlanet.h"
#include "../Interfaces/Colored.h"
#include "../3DRenderer/Mesh/ColoredMesh.h"

#include <vector>

class ColoredPlanet : public RenderablePlanet, public Colored
{
public:
	ColoredPlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
				  float scale, const std::string& identifier, std::shared_ptr<ShaderManager> shaderManager, const glm::vec4& color);
	virtual ~ColoredPlanet() {}

	virtual void render(std::shared_ptr<SceneContext> sceneContext) const override;
	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui) override;

private:
	ColoredMesh mesh;
};

