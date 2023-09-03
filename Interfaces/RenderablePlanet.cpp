#include "RenderablePlanet.h"

RenderablePlanet::RenderablePlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
								   float scale, const std::string& identifier, std::shared_ptr<ShaderManager> shaderManager, unsigned int sectors, unsigned int stacks)
	: Planet(position, velocity, mass, radius, scale, identifier, sectors, stacks)
	, Renderable(shaderManager)
	, lastRealOrbitUpdate(0.0f)
	, renderOrbit(false)
	, orbitDataUpdateIntervalInSec(0.1f)
	, worldScale({ 1.495978707f, 10 })
	, orbitInWorldSpace(150, { 1.0f, 1.0f, 1.0f }, shaderManager)
{
}

glm::mat4 RenderablePlanet::getModelMatrix() const
{
	glm::mat4 model(1.0f);

	auto pos = position / worldScale;
	auto sc = (radius / worldScale) * scale;

	model = glm::translate(model, pos.getGlmVec());
	model = glm::scale(model, glm::vec3(sc, sc, sc));
	model = glm::rotate(model, glm::radians(270.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	return model;
}

void RenderablePlanet::editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID, bool beginImGui)
{
	if (beginImGui)
	{
		ImGui::Begin(("Edit planet " + std::to_string(windowID)).c_str());
	}
	else
	{
		ImGui::Separator();
	}

	Planet::editViaImGui(objectHandler, windowID, false);

	ImGui::Separator();
	ImGui::Text("Orbit settings");
	ImGui::Checkbox("Render orbit", &renderOrbit);
	glm::vec3 color = orbitInWorldSpace.getColor();
	if (ImGui::ColorEdit3("Color", glm::value_ptr(color)))
	{
		orbitInWorldSpace.setColor(color);
	}
	int orbitMaxSize = static_cast<int>(orbitInWorldSpace.getMaxSize());
	if (ImGui::InputInt("Max size", &orbitMaxSize))
	{
		if (orbitMaxSize > 0)
		{
			orbitInWorldSpace.setMaxSize(orbitMaxSize);
		}
	}
	ImGui::DragFloat("Update interval", &orbitDataUpdateIntervalInSec, 0.01f, 0.01f, 100.0f);

	if (beginImGui)
	{
		ImGui::End();
	}
}

void RenderablePlanet::update(float simInSec, float realTimeInSec)
{
	if (lastRealOrbitUpdate >= orbitDataUpdateIntervalInSec && canMove)
	{
		orbitInWorldSpace.addPoint(getPositionInWorldSpace());
		lastRealOrbitUpdate = 0.0f;
	}
	else
	{
		lastRealOrbitUpdate += realTimeInSec;
	}

	Planet::update(simInSec);
}

float RenderablePlanet::getRadiusInWorldSpace() const
{
	return (radius / worldScale).getValue() * scale;
}

glm::vec3 RenderablePlanet::getPositionInWorldSpace() const
{
	return (position / worldScale).getGlmVec();
}
