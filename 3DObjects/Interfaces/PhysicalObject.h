#pragma once

#include "Moveable.h"
#include "Scaleable.h"

class PhysicalObject : public Moveable, public Scaleable {
public:
	PhysicalObject(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass, float scale)
		: Moveable(position)
		, Scaleable(scale)
		, velocity(velocity)
		, mass(mass) {}

	Measure<3> getVelocity() const { return this->velocity; }
	void setVelocity(const Measure<3>& velocity) { this->velocity = velocity; }

	void setMass(const Measure<1>& mass) { this->mass = mass; }
	Measure<1> getMass() const { return this->mass; }

	virtual ~PhysicalObject() {}

protected:
	Measure<3> velocity;
	Measure<1> mass;
};