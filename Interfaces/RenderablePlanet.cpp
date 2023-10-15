#include "RenderablePlanet.h"

RenderablePlanet::RenderablePlanet() : RenderablePlanet({}, {}, {}, {}, 1.0f, "")
{
}

RenderablePlanet::RenderablePlanet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
								   float scale, const std::string& identifier, unsigned int sectors, unsigned int stacks)
	: Planet(position, velocity, mass, radius, scale, identifier, sectors, stacks)
	, lastRealOrbitUpdate(0.0f)
	, renderOrbit(false)
	, orbitDataUpdateIntervalInSec(0.1f)
	, worldScale({ 1.495978707f, 10 })
	, orbitInWorldSpace(150, { 1.0f, 1.0f, 1.0f })
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

	Planet::editViaImGui(objectHandler, windowID, false);

	if (ImGui::CollapsingHeader("Orbit"))
	{
		ImGui::Checkbox("Render orbit", &renderOrbit);

		ImGui::PushItemWidth(291.0f);
		glm::vec3 color = orbitInWorldSpace.getColor();
		if (ImGui::ColorEdit3("Color", glm::value_ptr(color)))
		{
			orbitInWorldSpace.setColor(color);
		}
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(100.0f);
		int orbitMaxSize = static_cast<int>(orbitInWorldSpace.getMaxSize());
		if (ImGui::InputInt("Max size", &orbitMaxSize))
		{
			if (orbitMaxSize > 0)
			{
				orbitInWorldSpace.setMaxSize(orbitMaxSize);
			}
		}

		ImGui::DragFloat("Update interval", &orbitDataUpdateIntervalInSec, 0.01f, 0.01f, 100.0f);
		ImGui::PopItemWidth();
	}

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

void RenderablePlanet::serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version)
{
	outputArchive& canMove;
	outputArchive& identifier;
	outputArchive& mass;
	//material
	outputArchive& position;
	outputArchive& radius;
	outputArchive& scale;
	outputArchive& velocity;
}

void RenderablePlanet::serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version)
{
	inputArchive& canMove;
	inputArchive& identifier;
	inputArchive& mass;
	//material
	inputArchive& position;
	inputArchive& radius;
	inputArchive& scale;
	inputArchive& velocity;
}
