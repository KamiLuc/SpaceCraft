#pragma once

#include "../Interfaces/RenderablePlanet.h"
#include "../Interfaces/Textured.h"
#include "../3DRenderer/Mesh/TexturedMesh.h"
#include "../Utils/Functions.h"

class TexturedPlanet : public RenderablePlanet, public Textured
{
public:
	TexturedPlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass, const Measure<1>& radius,
		float scale, const std::string& identifier, std::shared_ptr<ShaderManager> shaderManager, const Texture& texture);

	virtual void render(std::shared_ptr<SceneContext> sceneContext) const override;
	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID);

private:
	TexturedMesh mesh;
};
