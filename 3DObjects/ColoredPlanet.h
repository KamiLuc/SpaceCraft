#pragma once

#include "Interfaces/RenderablePlanet.h"
#include "Interfaces/Colored.h"
#include "3DRenderer/Mesh/ColoredMesh.h"

#include <vector>

class ColoredPlanet : public RenderablePlanet, public Colored
{
public:
	ColoredPlanet();
	ColoredPlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
				  float scale, const std::string& identifier, const glm::vec4& color);
	virtual ~ColoredPlanet() {}

	virtual void render(SceneContext& sceneContext) const override;
	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui) override;
	virtual SerializableObjectId getSerializabledId() const override;
	virtual void serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version);
	virtual void serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version);

	void setColor(const glm::vec4 color);

private:
	ColoredMesh mesh;

	void setUpMesh();
};

