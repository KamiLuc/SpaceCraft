#pragma once

#include "TexturedPlanet.h"
#include "3DRenderer/Light/PointLight.h"

class TexturedStar : public TexturedPlanet, PointLight
{
	TexturedStar();
	TexturedStar(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
				 float scale, const std::string& identifier, std::shared_ptr<Texture> texture);
	virtual ~TexturedStar() {}
};
