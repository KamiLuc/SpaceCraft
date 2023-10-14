#pragma once

#include "3DObjects/ColoredPlanet.h"
#include "3DObjects/TexturedPlanet.h"

#include <list>

//zmienic create/build

class PlanetCreator
{
public:
	PlanetCreator(
		std::shared_ptr<TextureManager> textureManager, std::list<std::shared_ptr<Renderable>>& renderContainer,
		std::list<std::shared_ptr<RenderablePlanet>>& planetContainer);
	virtual ~PlanetCreator() {}

	void createColoredPlanetFromArchive(boost::archive::text_iarchive& ar);
	std::shared_ptr<ColoredPlanet> createColoredPlanet(
		const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
		const PhysicalUnit& radius, float scale, const std::string& identifier, const glm::vec4& color);

	void createTexturedPlanetFromArchive(boost::archive::text_iarchive& ar);
	std::shared_ptr<TexturedPlanet> CreateColoredPlanet(
		const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
		const PhysicalUnit& radius, float scale, const std::string& identifier, std::shared_ptr<Texture> texture);

private:

	template<typename Object>
	void addObjectToContainers(Object object)
	{
		renderContainer.emplace_back(object);
		planetContainer.emplace_back(object);
	}

	std::list<std::shared_ptr<Renderable>>& renderContainer;
	std::list<std::shared_ptr<RenderablePlanet>>& planetContainer;
	std::shared_ptr<TextureManager> textureManager;
};
