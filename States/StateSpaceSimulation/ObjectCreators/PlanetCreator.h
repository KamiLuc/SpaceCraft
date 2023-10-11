#pragma once

#include "3DRenderer/Shader/ShaderManager.h"
#include "3DObjects/ColoredPlanet.h"
#include "3DObjects/TexturedPlanet.h"

#include <list>

class PlanetCreator
{
public:
	PlanetCreator(
		std::shared_ptr<ShaderManager> shaderManager, std::list<std::shared_ptr<Renderable>>& renderContainer,
		std::list<std::shared_ptr<RenderablePlanet>>& planetContainer);
	virtual ~PlanetCreator() {}

	bool createColoredPlanetFromString(const std::string& data);
	std::shared_ptr<ColoredPlanet> createColoredPlanet(
		const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
		const PhysicalUnit& radius, float scale, const std::string& identifier, const glm::vec4& color);

	bool createTexturedPlanetFromString(const std::string& data);
	std::shared_ptr<TexturedPlanet> createTexturedPlanet(
		const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass,
		const PhysicalUnit& radius, float scale, const std::string& identifier, std::shared_ptr<Texture> texture);

private:
	std::list<std::shared_ptr<Renderable>>& renderContainer;
	std::list<std::shared_ptr<RenderablePlanet>>& planetContainer;
	std::shared_ptr<ShaderManager> shaderManager;
};
