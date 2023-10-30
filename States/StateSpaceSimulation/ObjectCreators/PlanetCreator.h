#pragma once

#include "3DObjects/ColoredPlanet.h"
#include "3DObjects/TexturedPlanet.h"
#include "3DObjects/TexturedStar.h"
#include "../ObjectEditor/RenderablePlanetObjectEditor.h"

#include <list>

class PlanetCreator
{
public:
	PlanetCreator(std::shared_ptr<TextureManager> textureManager, std::list<std::shared_ptr<PointLight>>& pointLightContainer);
	virtual ~PlanetCreator() {}

	void drawEditors();

	void createColoredPlanetFromArchive(boost::archive::text_iarchive& ar);
	std::shared_ptr<ColoredPlanet> buildColoredPlanet(
		const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
		const PhysicalUnit& radius, float scale, const std::string& identifier, const glm::vec4& color);

	void createTexturedPlanetFromArchive(boost::archive::text_iarchive& ar);
	std::shared_ptr<TexturedPlanet> buildTexturedPlanet(
		const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
		const PhysicalUnit& radius, float scale, const std::string& identifier, std::shared_ptr<Texture> texture);

	void createTexturedStarFromArchive(boost::archive::text_iarchive& ar);
	std::shared_ptr<TexturedStar> buildTexturedStar(
		const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
		const PhysicalUnit& radius, float scale, const std::string& identifier, std::shared_ptr<Texture> texture);

	void clearObjects();
	void removePlanetFromSimulation(std::shared_ptr<RenderablePlanet> planet);
	std::shared_ptr<TextureManager> getTextureManager();
	std::list<std::shared_ptr<Renderable>>& getRenderContainerRef();
	std::list<std::shared_ptr<RenderablePlanet>>& getPlanetContainerRef();

private:

	template<typename Object>
	void addObjectToContainers(Object object)
	{
		renderContainer.emplace_back(object);
		planetContainer.emplace_back(object);
	}

	RenderablePlanetObjectEditor coloredPlanetEditor;
	RenderablePlanetObjectEditor texturedPlanetEditor;
	RenderablePlanetObjectEditor texturedStarEditor;
	std::list<std::shared_ptr<Renderable>> renderContainer;
	std::list<std::shared_ptr<RenderablePlanet>> planetContainer;
	std::list<std::shared_ptr<PointLight>>& pointLightContainer;
	std::shared_ptr<TextureManager> textureManager;
};
