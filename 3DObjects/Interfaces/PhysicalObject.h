#pragma once

#include "Moveable.h"

#include <string>

class PhysicalObject : public Moveable {
public:
	PhysicalObject(const glm::vec<3, Measure>& position, const glm::vec<3, Measure>& velocity, const Measure& mass, const std::string& identifier)
		: Moveable(position), velocity(velocity), mass(mass), identifier(identifier) {}

	glm::vec<3, Measure> getVelocity() const { return this->velocity; }
	Measure getMass() const { return this->mass; }
	const std::string& getIdentifier() const { return this->identifier; }

protected:
	glm::vec<3, Measure> velocity;
	Measure mass;
	std::string identifier;
};