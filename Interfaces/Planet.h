#pragma once

#include "../3DRenderer/Material.h"
#include "PhysicalObject.h"
#include "EditableViaImGui.h"
#include "WithIdentifier.h"
#include "Sphere.h"

class Planet : public PhysicalObject, public EditableViaImGui, public WithIdentifier, public Sphere
{
public:
	Planet(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, const PhysicalUnit& radius,
		float scale, const std::string& identifier, unsigned int sectors = 32, unsigned int stacks = 32,
		float specularIntensity = 0.3f, float shininess = 4.0f)
		: PhysicalObject(position, velocity, mass, scale)
		, WithIdentifier(identifier)
		, Sphere(radius, stacks, sectors)
		, material(specularIntensity, shininess)
	{}
	virtual ~Planet() {}

	void update(float timeInSec);

	virtual void editViaImGui(ImGuiEditableObjectsHandler& objectHandler, unsigned int windowID) override;

protected:
	Material material;
};

