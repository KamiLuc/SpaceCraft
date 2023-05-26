#pragma once

#include "Moveable.h"
#include "Scaleable.h"

#include <string>

class PhysicalObject : public Moveable, public Scaleable {
public:
	PhysicalObject(const Measure<3>& position, const Measure<3>& velocity, const Measure<1>& mass, float scale, const std::string& identifier)
		: Moveable(position), Scaleable(scale), velocity(velocity), mass(mass), identifier(identifier) {}

	Measure<3> getVelocity() const { return this->velocity; }
	void setVelocity(const Measure<3>& velocity) { this->velocity = velocity; }

	void setMass(const Measure<1>& mass) { this->mass = mass; }
	Measure<1> getMass() const { return this->mass; }

	void setIdentifier(const std::string& identifier) { this->identifier = identifier; }
	std::string getIdentifier() const { return this->identifier; }
	virtual ~PhysicalObject() {}

protected:
	Measure<3> velocity;
	Measure<1> mass;
	std::string identifier;
};