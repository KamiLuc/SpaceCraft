#pragma once

#include <string>

class WithIdentifier {
public:
	WithIdentifier(const std::string& identifier)
		: identifier(identifier)
	{
	}

	std::string getIdentifier() const { return identifier; }
	void setIdentifier(const std::string& identifier) { this->identifier = identifier; }

protected:
	std::string identifier;
};