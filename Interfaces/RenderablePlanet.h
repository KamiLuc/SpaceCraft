#pragma once

#include "Renderable.h"
#include "Planet.h"

class RenderablePlanet : public Planet, public Renderable {
public:
	RenderablePlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
		float scale, const std::string& identifier, std::shared_ptr<ShaderManager> shaderManager, unsigned int sectors = 32, unsigned int stacks = 32);

	virtual glm::mat4 getModelMatrix() const override;
	virtual ~RenderablePlanet() {}

protected:
	
};
