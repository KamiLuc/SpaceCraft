#pragma once

#include "3DObjects/Orbit.h"
#include "AppFramework/Serializer/Serializable.h"
#include "AppFramework/GUI/EditableViaGui.h"
#include "Renderable.h"
#include "Interfaces/Sphere.h"
#include "Utils/PhysicalUnitVec.h"
#include "Interfaces/PhysicalObject.h"

#include <glm/gtc/type_ptr.hpp>

class RenderablePlanet : public Renderable, public Serializable, public EditableViaGui, public Sphere, public PhysicalObject
{
public:
	RenderablePlanet();
	RenderablePlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
					 float scale, const std::string& identifier, unsigned int sectors = 32, unsigned int stacks = 32);
	virtual ~RenderablePlanet() {}

	glm::mat4 getModelMatrix() const;
	void serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version) override;
	void serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version) override;
	void update(float simTimeInSec, float realTimeInSec);
	void setIdentifier(const std::string& identifier);
	float getRadiusInWorldSpace() const;
	std::string getIdentifier() const;
	glm::vec3 getPositionInWorldSpace() const;

protected:
	Material material;
	Orbit orbitInWorldSpace;
	std::string identifier;
	const PhysicalUnit worldScale;
	float lastRealOrbitUpdate;
	float orbitDataUpdateIntervalInSec;
	bool renderOrbit;

	void editViaGui() override;
};
