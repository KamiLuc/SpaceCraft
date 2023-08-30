#pragma once

#include "Moveable.h"
#include "Scaleable.h"

class PhysicalObject : public Moveable, public Scaleable {
public:
	PhysicalObject(const PhysicalUnitVec<3>& position, const PhysicalUnitVec<3>& velocity, const PhysicalUnit& mass, float scale)
		: Moveable(position)
		, Scaleable(scale)
		, velocity(velocity)
		, mass(mass) {}

	PhysicalUnitVec<3> getVelocity() const { return this->velocity; }
	void setVelocity(const PhysicalUnitVec<3>& velocity) { this->velocity = velocity; }

	void setMass(const PhysicalUnit& mass) { this->mass = mass; }
	PhysicalUnit getMass() const { return this->mass; }

	virtual ~PhysicalObject() {}

protected:
	PhysicalUnitVec<3> velocity;
	PhysicalUnit mass;
};