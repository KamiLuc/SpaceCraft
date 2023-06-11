#include "UniformLocations.h"

UniformLocations::UniformLocations()
	: uniformModel(-1)
	, uniformProjection(-1)
	, uniformView(-1)
	, uniformAmbientColor(-1)
	, uniformAmbientIntensity(-1)
	, uniformCameraPosition(-1)
	, uniformDiffuseIntensity(-1)
	, uniformLightDirection(-1)
	, uniformSpecularIntensity(-1)
	, uniformShininess(-1)
	, uniformWorldScale(-1) {}

void UniformLocations::clear()
{
	uniformProjection = 0;
	uniformModel = 0;
	uniformView = 0;
	uniformAmbientIntensity = 0;
	uniformAmbientColor = 0;
	uniformDiffuseIntensity = 0;
	uniformLightDirection = 0;
	uniformCameraPosition = 0;
	uniformSpecularIntensity = 0;
	uniformShininess = 0;
	uniformWorldScale = 0;
}
