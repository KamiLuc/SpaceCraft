#pragma once

#include "../../Utils/Measure.h"
#include "PhysicalObject.h"
#include "Renderable.h"
#include "EditableViaImGui.h"
#include "WithIdentifier.h"

class Planet : public PhysicalObject, public Renderable, public EditableViaImGui, public WithIdentifier
{
public:
	Planet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass, const Measure<1>& radius,
		float scale, const std::string& identifier, const Shader& shader)
		: PhysicalObject(position, velocity, mass, scale)
		, Renderable(shader)
		, WithIdentifier(identifier)
		, radius(radius)
		, worldScale1({ 1.495978707f, 10 })
		, worldScale3({ 1.495978707f, 1.495978707f, 1.495978707f }, 10)
	{}
	virtual ~Planet() {}

	void update(float timeInSec);

	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID) override = 0;
	Measure<3> getPositionInWorldSpace() const;

protected:
	Measure<1> radius;
	const Measure<1> worldScale1;
	const Measure<3> worldScale3;
};

