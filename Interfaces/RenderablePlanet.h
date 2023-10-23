#pragma once

#include "3DObjects/Orbit.h"
#include "AppFramework/Serializer/Serializable.h"
#include "Renderable.h"
#include "Planet.h"

#include <glm/gtc/type_ptr.hpp>

class RenderablePlanet : public Planet, public Renderable, public Serializable
{
public:
	RenderablePlanet();
	RenderablePlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
					 float scale, const std::string& identifier, unsigned int sectors = 32, unsigned int stacks = 32);

	virtual ~RenderablePlanet() {}
	virtual glm::mat4 getModelMatrix() const;
	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui) override;
	virtual void serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version) override;
	virtual void serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version) override;

	void update(float simTimeInSec, float realTimeInSec);
	float getRadiusInWorldSpace() const;
	glm::vec3 getPositionInWorldSpace() const;

protected:
	const PhysicalUnit worldScale;
	Orbit orbitInWorldSpace;
	float lastRealOrbitUpdate;
	float orbitDataUpdateIntervalInSec;
	bool renderOrbit;
};
