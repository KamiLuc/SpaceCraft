#pragma once

#include "../../Utils/Measure.h"
#include "PhysicalObject.h"
#include "Renderable.h"
#include "EditableViaImGui.h"

class Planet : public PhysicalObject, public Renderable, public EditableViaImGui
{
public:
	Planet(const glm::vec<3, Measure>& position, const glm::vec<3, Measure>& velocity, const Measure& mass,
		float scale, const std::string& identifier, const Shader& shader)
		:
		PhysicalObject(position, velocity, mass, scale, identifier),
		Renderable(shader) {}

	virtual bool editViaImGui() override = 0;

private:

};

