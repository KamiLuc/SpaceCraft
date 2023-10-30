#include "PlanetCreator.h"

PlanetCreator::PlanetCreator(
	std::shared_ptr<TextureManager> textureManager, std::list<std::shared_ptr<PointLight>>& pointLightContainer)
	: textureManager(textureManager)
	, pointLightContainer(pointLightContainer)
	, coloredPlanetEditor("Edit colored planet", { 410, 300 }, { 410, 1000 }, textureManager.get())
	, texturedPlanetEditor("Edit textured planet", { 410, 300 }, { 410, 1000 }, textureManager.get())
	, texturedStarEditor("Edit textured star", { 410, 300 }, { 410, 1000 }, textureManager.get())
{
}

void PlanetCreator::drawEditors()
{
	coloredPlanetEditor.draw();
	texturedPlanetEditor.draw();
	texturedStarEditor.draw();
}

void PlanetCreator::createColoredPlanetFromArchive(boost::archive::text_iarchive& ar)
{
	auto object = std::make_shared<ColoredPlanet>();
	ar & *object;
	object->registerEditor(&coloredPlanetEditor);
	addObjectToContainers(object);
}

std::shared_ptr<ColoredPlanet> PlanetCreator::buildColoredPlanet(
	const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
	float scale, const std::string& identifier, const glm::vec4& color)
{
	auto object = std::make_shared<ColoredPlanet>(position, velocity, mass, radius, scale, identifier, color);
	object->registerEditor(&coloredPlanetEditor);
	addObjectToContainers(object);
	return object;
}

void PlanetCreator::createTexturedPlanetFromArchive(boost::archive::text_iarchive& ar)
{
	auto object = std::make_shared<TexturedPlanet>();
	ar & *object;
	object->setTexture(textureManager->getTexture(object->getSerializedTextureName()));
	object->registerEditor(&texturedPlanetEditor);
	addObjectToContainers(object);
}

std::shared_ptr<TexturedPlanet> PlanetCreator::buildTexturedPlanet(
	const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
	float scale, const std::string& identifier, std::shared_ptr<Texture> texture)
{
	auto object = std::make_shared<TexturedPlanet>(position, velocity, mass, radius, scale, identifier, texture);
	object->registerEditor(&texturedPlanetEditor);
	addObjectToContainers(object);
	return object;
}

void PlanetCreator::createTexturedStarFromArchive(boost::archive::text_iarchive& ar)
{
	auto object = std::make_shared<TexturedStar>();
	ar & *object;
	object->setTexture(textureManager->getTexture(object->getSerializedTextureName()));
	object->registerEditor(&texturedStarEditor);
	addObjectToContainers(object);
	pointLightContainer.push_back(object);
}

std::shared_ptr<TexturedStar> PlanetCreator::buildTexturedStar(
	const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
	float scale, const std::string& identifier, std::shared_ptr<Texture> texture)
{
	auto object = std::make_shared<TexturedStar>(position, velocity, mass, radius, scale, identifier, texture);
	object->registerEditor(&texturedStarEditor);
	addObjectToContainers(object);
	pointLightContainer.push_back(object);
	return object;
}

void PlanetCreator::clearObjects()
{
	for (const auto& planet : planetContainer)
	{
		planet->unregisterEditor();
	}

	renderContainer.clear();
	planetContainer.clear();
	pointLightContainer.clear();
}

void PlanetCreator::removePlanetFromSimulation(std::shared_ptr<RenderablePlanet> planet)
{
	planet->unregisterEditor();
	renderContainer.remove(planet);
	planetContainer.remove(planet);

	auto p = std::dynamic_pointer_cast<PointLight>(planet);
	if (p)
	{
		pointLightContainer.remove(p);
	}
}

std::shared_ptr<TextureManager> PlanetCreator::getTextureManager()
{
	return textureManager;
}

std::list<std::shared_ptr<Renderable>>& PlanetCreator::getRenderContainerRef()
{
	return renderContainer;
}

std::list<std::shared_ptr<RenderablePlanet>>& PlanetCreator::getPlanetContainerRef()
{
	return planetContainer;
}
