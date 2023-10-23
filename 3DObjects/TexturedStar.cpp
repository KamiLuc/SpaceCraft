#include "TexturedStar.h"

TexturedStar::TexturedStar()
{
}

TexturedStar::TexturedStar(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit & mass,
						   const PhysicalUnit & radius, float scale, const std::string & identifier, std::shared_ptr<Texture> texture)
	: TexturedPlanet(position, velocity, mass, radius, scale, identifier, texture)
	, PointLight({ 1.0f, 1.0f, 1.0f }, 1.0f, TexturedPlanet::getPositionInWorldSpace(), 1.0f, 0.1f, 0.1f, 0.1f)
{
}
