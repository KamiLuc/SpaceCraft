#pragma once

#include <AppFramework/EventManager/EventManager.h>
#include "AppFramework/GUI/EditableViaGui.h"
#include "Interfaces/RenderablePlanet.h"
#include "Utils/PhysicalUnit.h"

struct SpaceSimulationSettings : public EditableViaGui
{
public:
	SpaceSimulationSettings(bool pauseSimulation = false, bool renderCoordinateAxes = false, float* coordinateAxesWidth = nullptr,
							PhysicalUnit simulationSpeed = PhysicalUnit(), EventManager* eventManager = nullptr)
		: pauseSimulation(pauseSimulation)
		, renderCoordinateAxes(renderCoordinateAxes)
		, coordinateAxesWidth(coordinateAxesWidth)
		, simulationSpeed(simulationSpeed)
		, eventManager(eventManager)
	{
	}

	bool pauseSimulation;
	bool renderCoordinateAxes;
	float* coordinateAxesWidth;
	PhysicalUnit simulationSpeed;
	std::shared_ptr<RenderablePlanet> focusedPlanet;

	void enableEvents() { eventManager->enableCallbacks(); }
	void disableEvents() { eventManager->disableCallbacks(); }

	void editViaGui() override
	{
		ImGui::Checkbox("Render coordinate system axis", &renderCoordinateAxes);
		ImGui::DragFloat("Axis line width", coordinateAxesWidth, 0.1f, 1.0f, 30.0f);

		ImGui::Separator();
		ImGui::Checkbox("Pause simulation", &pauseSimulation);
		ImGui::InputFloat("Simulation speed", simulationSpeed.getBasePtr());
		ImGui::InputInt("Simulation speed exponent", simulationSpeed.getExponentPtr());
	};

private:
	EventManager* eventManager;
};
