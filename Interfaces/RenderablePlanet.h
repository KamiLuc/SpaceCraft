#pragma once

#include "../3DObjects/Orbit.h"
#include "Renderable.h"
#include "Planet.h"

#include <glm/gtc/type_ptr.hpp>

class RenderablePlanet : public Planet, public Renderable {
public:
	RenderablePlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
		float scale, const std::string& identifier, std::shared_ptr<ShaderManager> shaderManager, unsigned int sectors = 32, unsigned int stacks = 32);
	
	virtual ~RenderablePlanet() {}
	virtual glm::mat4 getModelMatrix() const;
	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui) override;
	
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
