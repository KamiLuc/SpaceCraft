#include "PlanetCreator.h"

PlanetCreator::PlanetCreator(
	std::shared_ptr<ShaderManager> shaderManager, std::list<std::shared_ptr<Renderable>>& renderContainer,
	std::list<std::shared_ptr<RenderablePlanet>>& planetContainer)
	: shaderManager(shaderManager)
	, renderContainer(renderContainer)
	, planetContainer(planetContainer)
{
}

bool PlanetCreator::createColoredPlanetFromString(const std::string& data)
{
	return false;
}

std::shared_ptr<ColoredPlanet> PlanetCreator::createColoredPlanet(
	const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
	float scale, const std::string& identifier, const glm::vec4& color)
{
	auto object = std::make_shared<ColoredPlanet>(position, velocity, mass, radius, scale, identifier, color);
	renderContainer.emplace_back(object);
	planetContainer.emplace_back(object);
	return object;
}

bool PlanetCreator::createTexturedPlanetFromString(const std::string& data)
{
	return false;
}

std::shared_ptr<TexturedPlanet> PlanetCreator::createTexturedPlanet(
	const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
	float scale, const std::string& identifier, std::shared_ptr<Texture> texture)
{
	auto object = std::make_shared<TexturedPlanet>(position, velocity, mass, radius, scale, identifier, texture);
	renderContainer.emplace_back(object);
	planetContainer.emplace_back(object);
	return object;
}
