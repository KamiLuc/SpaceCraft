#pragma once

#include "SerializableObjectId.h"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class Serializable
{
public:
	friend class boost::serialization::access;

	Serializable() {}
	virtual ~Serializable() {}

	virtual SerializableObjectId getSerializabledId() const { return SerializableObjectId::NONE; }
	virtual void serializeFromBase(boost::archive::text_oarchive& outputArchive, std::shared_ptr<Serializable> obj) { outputArchive &*obj; }

	virtual void serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version) = 0;
	virtual void serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version) = 0;
};