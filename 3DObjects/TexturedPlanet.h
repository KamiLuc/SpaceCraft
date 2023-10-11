#pragma once

#include "Interfaces/RenderablePlanet.h"
#include "Interfaces/Textured.h"
#include "3DRenderer/Mesh/TexturedMesh.h"
#include "Utils/Functions.h"

class TexturedPlanet : public RenderablePlanet, public Textured
{
public:
	TexturedPlanet();
	TexturedPlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
				   float scale, const std::string& identifier, std::shared_ptr<Texture> texture);
	virtual ~TexturedPlanet() {}

	virtual void render(SceneContext& sceneContext) const override;
	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui);
	virtual SerializableObjectId getSerializabledId() const override;
	virtual std::string serializeToString() const override;
	virtual bool deserializeFromString(const std::string& data) override;

private:
	TexturedMesh mesh;
};
