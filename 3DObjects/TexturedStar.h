#pragma once

#include "TexturedPlanet.h"
#include "3DRenderer/Light/PointLight.h"

class TexturedStar : public TexturedPlanet, public PointLight
{
public:
	TexturedStar();
	TexturedStar(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
				 float scale, const std::string& identifier, std::shared_ptr<Texture> texture);
	virtual ~TexturedStar() {}

	virtual void render(SceneContext& sceneContext) const override;
	virtual SerializableObjectId getSerializabledId() const override;
	virtual void serializeFromBase(boost::archive::text_oarchive& outputArchive, std::shared_ptr<Serializable> obj) override;
	virtual void serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version) override;
	virtual void serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version) override;

private:
	void editViaGui() override;
};
