#include "PlanetDistanceVisualizer.h"

PlanetDistanceVisualizer::PlanetDistanceVisualizer(std::list<std::shared_ptr<RenderablePlanet>>& planetsRef)
	: planetsListRef(planetsRef)
	, firstPlanetIndex(-1)
	, secondPlanetIndex(-1)
{
	plot.lastUpdate = ImGui::GetTime();
}

void PlanetDistanceVisualizer::editViaGui()
{
	planets.assign(planetsListRef.begin(), planetsListRef.end());

	if (planets.size() > 0)
	{
		drawCombo("First planet", firstPlanetIndex);
		drawCombo("Second planet", secondPlanetIndex);

		ImGui::Separator();
		if (firstPlanetIndex != -1 && secondPlanetIndex != -1)
		{
			auto distance = (planets[firstPlanetIndex]->getPosition() - planets[secondPlanetIndex]->getPosition()).getLength();
			distance.convertTo(11);
			std::string text("Distance = ");
			text.append(std::to_string(distance.getBase()));
			text.append(" * 10^");
			text.append(std::to_string(distance.getExponent()));
			ImGui::Text(text.c_str());

			auto plotSize = static_cast<int>(plot.values.size());
			auto lastUpdateTime = ImGui::GetTime();
			float newPlotData = distance.getBase();
			if (lastUpdateTime - plot.lastUpdate > plot.refreshTime)
			{
				plot.values[plot.valuesOffset] = newPlotData;
				plot.valuesOffset = (plot.valuesOffset + 1) % plotSize;
				plot.lastUpdate = lastUpdateTime;
			}

			ImGui::PlotLines("", plot.values.data(), plotSize, plot.valuesOffset, nullptr, plot.min, plot.max, ImVec2(0, 80.0f));

			ImGui::DragFloat("Min value", &plot.min, 0.01f, 0.0f, 99999.0f);
			ImGui::DragFloat("Max value", &plot.max, 0.01f, 0.0f, 99999.0f);
		}
	}
	else
	{
		firstPlanetIndex = -1;
		secondPlanetIndex = -1;
		ImGui::Text("There are no planets in simulation");
	}
}

void PlanetDistanceVisualizer::drawCombo(const char* label, int& selectedIndex)
{
	if (ImGui::BeginCombo(label, selectedIndex != -1 ? planets[selectedIndex]->getIdentifier().c_str() : "Select Planet"))
	{
		for (unsigned int index = 0; index < planets.size(); ++index)
		{
			const bool is_selected = (index == selectedIndex);
			if (ImGui::Selectable((std::to_string(index + 1) + ". " + planets[index]->getIdentifier()).c_str(), is_selected))
			{
				selectedIndex = index;
			}

			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}
}
