#pragma once

#include "Interfaces/Colored.h"
#include "3DRenderer/Mesh/ColoredMesh.h"
#include "Interfaces/RenderablePlanet.h"


#include <vector>

class ColoredPlanet : public RenderablePlanet, public Colored
{
public:
	ColoredPlanet();
	ColoredPlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
				  const PhysicalUnit& radius, float scale, const std::string& identifier, const glm::vec4& color);

	void render(SceneContext& sceneContext) const override;
	void serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version);
	void serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version);
	void serializeFromBase(boost::archive::text_oarchive& outputArchive, std::shared_ptr<Serializable> obj) override;
	SerializableObjectId getSerializabledId() const override;

private:
	ColoredMesh mesh;

	void setUpMesh();
	void editViaGui() override;
	void setColor(const glm::vec4& color);

};

