#pragma once

#include "Interfaces/Textured.h"
#include "Interfaces/RenderablePlanet.h"
#include "3DRenderer/Mesh/TexturedMesh.h"

class TexturedPlanet : public RenderablePlanet, public Textured
{
public:
	TexturedPlanet();
	TexturedPlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
				   float scale, const std::string& identifier, std::shared_ptr<Texture> texture);
	virtual ~TexturedPlanet() {}

	std::string getSerializedTextureName() const;
	SerializableObjectId getSerializabledId() const override;
	void render(SceneContext& sceneContext) const override;
	void serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version) override;
	void serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version) override;
	void serializeFromBase(boost::archive::text_oarchive& outputArchive, std::shared_ptr<Serializable> obj) override;

protected:
	TexturedMesh mesh;
	std::string serializedTextureName;

	void setUpMesh();
	void editViaGui() override;
};
