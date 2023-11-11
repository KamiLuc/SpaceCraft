#pragma once

#include "AppFramework/GUI/EditableViaGui.h"

#include <Interfaces/RenderablePlanet.h>
#include <array>
#include <limits>

class PlanetDistanceVisualizer : public EditableViaGui
{
public:
	PlanetDistanceVisualizer(std::list< std::shared_ptr<RenderablePlanet>>& planetsRef);

private:
	void editViaGui() override;
	void drawCombo(const char* label, int& selectedIndex);

	struct
	{
		std::array<float, 300> values = {};
		int valuesOffset = 0;
		float min = 0.0f;
		float max = 5.0f;
		float refreshTime = 1 / 60.0f;
		double lastUpdate = 0.0;

	} plot;

	int firstPlanetIndex = -1;
	int secondPlanetIndex = -1;
	std::list<std::shared_ptr<RenderablePlanet>>& planetsListRef;
	std::vector<std::shared_ptr<RenderablePlanet>> planets;
};

