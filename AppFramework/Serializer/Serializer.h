#pragma once

#include "Serializable.h"

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <sstream>
#include <map>
#include <list>
#include <functional>

class Serializer
{
public:
	Serializer() {}
	virtual ~Serializer() {}

	std::filesystem::path getSaveDirectiory() const { return saveDirectory; }
	void setSaveDirectiory(const std::filesystem::path& filePath) { this->saveDirectory = filePath; }
	void registerObjectCreator(SerializableObjectId objectId, std::function<void(boost::archive::text_iarchive& ar)> creationFunction);
	void createSerializedObjects(const std::filesystem::path& filePath);

	template <typename InputIterator>
	void serializeObjects(const std::filesystem::path& filePath, InputIterator begin, InputIterator end) const;

private:
	std::filesystem::path saveDirectory;
	std::map<SerializableObjectId, std::function<void(boost::archive::text_iarchive& ar)>> creators;

	void closeFile(std::fstream& file) const;
	void serializeSingleObject(std::shared_ptr<Serializable> object, boost::archive::text_oarchive& ar) const;
	std::fstream openFile(const std::filesystem::path& filePath, unsigned int openmode) const;
};

inline std::fstream Serializer::openFile(const std::filesystem::path& filePath, unsigned int openmode) const
{
	if (filePath.empty())
	{
		std::string exceptionMessage { std::move(std::string(__func__).append("SaveDirectiory is empty")) };
		printf(exceptionMessage.c_str());
		throw std::runtime_error(exceptionMessage.c_str());
	}

	std::fstream file(filePath, openmode);

	if (!file.is_open())
	{
		std::string exceptionMessage { std::move(std::string(__func__).append("Unable to create or open file: ").append(filePath.string())) };
		printf(exceptionMessage.c_str());
		throw std::runtime_error(exceptionMessage.c_str());
	}

	return file;
}

inline void Serializer::closeFile(std::fstream& file) const
{
	file.close();
}

inline void Serializer::serializeSingleObject(std::shared_ptr<Serializable> object, boost::archive::text_oarchive& ar) const
{
	ar & object->getSerializabledId();
	object->serializeFromBase(ar, object);
}

inline void Serializer::registerObjectCreator(SerializableObjectId objectId, std::function<void(boost::archive::text_iarchive& ar)> creationFunction)
{
	creators[objectId] = creationFunction;
}

inline void Serializer::createSerializedObjects(const std::filesystem::path& filePath)
{
	auto file = openFile(filePath, std::ios::in);
	boost::archive::text_iarchive ar(file);
	SerializableObjectId id = SerializableObjectId::NONE;

	while (true)
	{
		try
		{
			ar& id;
			if (!(creators.find(id) == creators.end()))
			{
				creators[id](ar);
			}
			else
			{
				printf("%s: ObjectId = %d is not present in registered creators", __func__, static_cast<uint32_t>(id));
			}

		}
		catch (const boost::archive::archive_exception& ex)
		{
			if (ex.code == boost::archive::archive_exception::input_stream_error)
			{
				break;
			}
			else
			{
				printf("%s: Fail occured during object creation ObjectId = %d", __func__, static_cast<uint32_t>(id));
			}
		}
	}

	closeFile(file);
}

template<typename InputIterator>
inline void Serializer::serializeObjects(const std::filesystem::path& filePath, InputIterator begin, InputIterator end) const
{
	auto file = openFile(filePath, std::ios::in | std::ios::out | std::ios::trunc);
	boost::archive::text_oarchive ar(file);

	while (begin != end)
	{
		serializeSingleObject(*begin, ar);
		++begin;
	}

	closeFile(file);
}
