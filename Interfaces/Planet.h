#pragma once

#include "../../Utils/Measure.h"
#include "../3DRenderer/Material.h"
#include "PhysicalObject.h"
#include "EditableViaImGui.h"
#include "WithIdentifier.h"
#include "Sphere.h"

class Planet : public PhysicalObject, public EditableViaImGui, public WithIdentifier, public Sphere
{
public:
	Planet(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass, const Measure<1>& radius,
		float scale, const std::string& identifier, unsigned int sectors = 32, unsigned int stacks = 32,
		float specularIntensity = 0.3f, float shininess = 4.0f)
		: PhysicalObject(position, velocity, mass, scale)
		, WithIdentifier(identifier)
		, Sphere(radius, stacks, sectors)
		, material(specularIntensity, shininess)
		, worldScale1({ 1.495978707f, 10 })
		, worldScale3({ 1.495978707f, 1.495978707f, 1.495978707f }, 10)
	{}
	virtual ~Planet() {}

	void update(float timeInSec);

	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID) override;
	Measure<3> getPositionInWorldSpace() const;
	Measure<1> getRadiusInWorldSpace() const;

protected:
	const Measure<1> worldScale1;
	const Measure<3> worldScale3;
	Material material;
};

