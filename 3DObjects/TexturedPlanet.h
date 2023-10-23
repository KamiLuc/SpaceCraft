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

	std::string getSerializedTextureName() const;

	virtual void render(SceneContext& sceneContext) const override;
	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui) override;
	virtual SerializableObjectId getSerializabledId() const override;
	virtual void serializeFromBase(boost::archive::text_oarchive& outputArchive, std::shared_ptr<Serializable> obj) override;
	virtual void serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version) override;
	virtual void serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version) override;

protected:
	TexturedMesh mesh;
	std::string serializedTextureName;

	void setUpMesh();
};
