#include "RenderablePlanet.h"

RenderablePlanet::RenderablePlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
	float scale, const std::string& identifier, std::shared_ptr<ShaderManager> shaderManager, unsigned int sectors, unsigned int stacks)
	: Planet(position, velocity, mass, radius, scale, identifier, sectors, stacks)
	, Renderable(shaderManager)
{
}

glm::mat4 RenderablePlanet::getModelMatrix() const
{
	glm::mat4 model(1.0f);

	auto pos = position / worldScale3;
	auto sc = (radius / worldScale1) * scale;

	model = glm::translate(model, pos.getGlmVec());
	model = glm::scale(model, glm::vec3(sc, sc, sc));
	model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	return model;
}
