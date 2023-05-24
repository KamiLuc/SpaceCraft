#pragma once

#include "Moveable.h"
#include "Scaleable.h"

#include <string>

class PhysicalObject : public Moveable, public Scaleable {
public:
	PhysicalObject(const glm::vec<3, Measure>& position, const glm::vec<3, Measure>& velocity, const Measure& mass, float scale, const std::string& identifier)
		: Moveable(position), Scaleable(scale), velocity(velocity), mass(mass), identifier(identifier) {}

	glm::vec<3, Measure> getVelocity() const { return this->velocity; }
	void setVelocity(glm::vec<3, Measure> velocity) { this->velocity = velocity; }

	void setMass(const Measure& mass) { this->mass = mass; }
	Measure getMass() const { return this->mass; }

	void setIdentifier(const std::string& identifier) { this->identifier = identifier; }
	std::string getIdentifier() const { return this->identifier; }

protected:
	glm::vec<3, Measure> velocity;
	Measure mass;
	std::string identifier;
};