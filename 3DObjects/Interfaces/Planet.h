#pragma once

#include "../../Utils/Measure.h"
#include "PhysicalObject.h"
#include "Renderable.h"
#include "ImGuiEditableObjectsHandler.h"

class Planet : public PhysicalObject, public Renderable, public EditableViaImGui
{
public:
	Planet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass,
		float scale, const std::string& identifier, const Shader& shader)
		:
		PhysicalObject(position, velocity, mass, scale, identifier),
		Renderable(shader) {}

	virtual void editViaImGui(ImGuiEditableObjectsHandler* objectHandler, unsigned int windowID) override = 0;

private:

};

