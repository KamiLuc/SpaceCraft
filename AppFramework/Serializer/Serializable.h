#pragma once

#include "SerializableObjectId.h"

#include <string>

class Serializable {
public:
	Serializable() {}
	virtual ~Serializable() {}

	virtual SerializableObjectId getSerializabledId() const = 0;
	virtual std::string serializeToString() const = 0;
	virtual bool deserializeFromString(const std::string& data) = 0;
};