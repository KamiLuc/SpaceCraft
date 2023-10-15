#include "PlanetCreator.h"

PlanetCreator::PlanetCreator(
	std::shared_ptr<TextureManager> textureManager, std::list<std::shared_ptr<Renderable>>& renderContainer,
	std::list<std::shared_ptr<RenderablePlanet>>& planetContainer)
	: textureManager(textureManager)
	, renderContainer(renderContainer)
	, planetContainer(planetContainer)
{
}

void PlanetCreator::createColoredPlanetFromArchive(boost::archive::text_iarchive& ar)
{
	auto object = std::make_shared<ColoredPlanet>();
	ar&* object;
	addObjectToContainers(object);
}

std::shared_ptr<ColoredPlanet> PlanetCreator::createColoredPlanet(
	const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
	float scale, const std::string& identifier, const glm::vec4& color)
{
	auto o = std::make_shared<ColoredPlanet>(position, velocity, mass, radius, scale, identifier, color);
	addObjectToContainers(o);
	return o;
}

void PlanetCreator::createTexturedPlanetFromArchive(boost::archive::text_iarchive& ar)
{
	auto object = std::make_shared<TexturedPlanet>();
	ar&* object;
	object->setTexture(textureManager->getTexture(object->getSerializedTextureName()));
	addObjectToContainers(object);
}

std::shared_ptr<TexturedPlanet> PlanetCreator::CreateColoredPlanet(
	const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
	float scale, const std::string& identifier, std::shared_ptr<Texture> texture)
{
	auto o = std::make_shared<TexturedPlanet>(position, velocity, mass, radius, scale, identifier, texture);
	addObjectToContainers(o);
	return o;
}
