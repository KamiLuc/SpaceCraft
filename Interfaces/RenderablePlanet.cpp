#include "RenderablePlanet.h"

RenderablePlanet::RenderablePlanet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass, const Measure<1>& radius, float scale, const std::string& identifier, const Shader& shader, unsigned int sectors, unsigned int stacks)
	: Planet(position, velocity, mass, radius, scale, identifier, sectors, stacks)
	, Renderable(shader)
{
}

glm::mat4 RenderablePlanet::getModelMatrix() const
{
	glm::mat4 model(1.0f);

	auto pos = position / worldScale3;
	auto sc = ((radius / worldScale1) * scale).getValuesInDesiredExponent(0)[0];

	model = glm::translate(model, pos.getGlmVec());
	model = glm::scale(model, glm::vec3(sc, sc, sc));
	model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	return model;
}
