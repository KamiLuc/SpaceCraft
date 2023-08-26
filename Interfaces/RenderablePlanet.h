#pragma once

#include "Renderable.h"
#include "Planet.h"

class RenderablePlanet : public Planet, public Renderable {
public:
	RenderablePlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass, const Measure<1>& radius,
		float scale, const std::string& identifier, std::shared_ptr<ShaderManager> shaderManager, unsigned int sectors = 32, unsigned int stacks = 32);

	virtual glm::mat4 getModelMatrix() const override;
	virtual ~RenderablePlanet() {}

protected:
	
};
