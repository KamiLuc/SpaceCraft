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

class Serializer {
public:
	Serializer(char separator = ',') : separator(separator) {}
	virtual ~Serializer() {}

	std::filesystem::path getFilePath() const { return filePath; }
	void setFilePath(const std::filesystem::path& filePath) { this->filePath = filePath; }
	void serializeObject(std::shared_ptr<Serializable> object) const;
	void registerObjectCreator(SerializableObjectId objectId, std::function<bool(const std::string&)> creationFunction);
	void createSerializedObjects();

	template <typename InputIterator>
	void serializeObjects(InputIterator begin, InputIterator end) const;

private:
	std::filesystem::path filePath;
	char separator;
	std::map<SerializableObjectId, std::function<bool(const std::string&)>> creators;

	std::list<std::string> loadSerializedData() const;
	std::fstream openFile() const;
	SerializableObjectId getObjectIdFromSerializedObject(const std::string& data) const;
	std::string getDataFromSerializedObject(const std::string& data) const;
	void closeFile(std::fstream& file) const;
	void serializeSingleObject(std::shared_ptr<Serializable> object, std::fstream& file) const;
};

inline std::list<std::string> Serializer::loadSerializedData() const
{
	auto file = openFile();
	std::string line;
	std::list<std::string> result;

	while (std::getline(file, line))
	{
		result.push_back(line);
	}

	return result;
}

inline std::fstream Serializer::openFile() const
{
	if (filePath.empty())
	{
		std::string exceptionMessage { std::move(std::string(__func__).append("filePath is empty")) };
		printf(exceptionMessage.c_str());
		throw std::runtime_error(exceptionMessage.c_str());
	}

	std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::trunc);

	if (!file.is_open())
	{
		std::string exceptionMessage { std::move(std::string(__func__).append("Unable to create or open file: ").append(filePath.string())) };
		printf(exceptionMessage.c_str());
		throw std::runtime_error(exceptionMessage.c_str());
	}

	return file;
}

inline SerializableObjectId Serializer::getObjectIdFromSerializedObject(const std::string& data) const
{
	std::istringstream ss(data);
	std::string id;
	std::getline(ss, id, separator);
	return static_cast<SerializableObjectId>(std::stoul(id));
}

inline std::string Serializer::getDataFromSerializedObject(const std::string& data) const
{
	size_t separatorPosition = data.find(separator);
	if (separatorPosition != std::string::npos)
	{
		return data.substr(separatorPosition + 1);
	}
	return "";
}

inline void Serializer::closeFile(std::fstream& file) const
{
	file.close();
}

inline void Serializer::serializeSingleObject(std::shared_ptr<Serializable> object, std::fstream& file) const
{
	file << static_cast<uint32_t>(object->getSerializabledId()) << separator << object->serializeToString() << "\n";
}

inline void Serializer::serializeObject(std::shared_ptr<Serializable> object) const
{
	auto file = openFile();
	serializeSingleObject(object, file);
	closeFile(file);
}

inline void Serializer::registerObjectCreator(SerializableObjectId objectId, std::function<bool(const std::string&)> creationFunction)
{
	creators[objectId] = creationFunction;
}

inline void Serializer::createSerializedObjects()
{
	auto data = loadSerializedData();

	for (const auto& singleSerializedObject : data)
	{
		auto objectId = getObjectIdFromSerializedObject(singleSerializedObject);
		auto objectData = getDataFromSerializedObject(singleSerializedObject);

		if (creators.find(objectId) != creators.end())
		{
			if (!creators.at(objectId)(objectData))
			{
				printf("%s: ObjectId = %d can not be created from data = %s", __func__, static_cast<uint32_t>(objectId), objectData.c_str());
			}
		}
		else
		{
			printf("%s: ObjectId = %d is not present in registered creators", __func__, static_cast<uint32_t>(objectId));
		}
	}
}

template<typename InputIterator>
inline void Serializer::serializeObjects(InputIterator begin, InputIterator end) const
{
	auto file = openFile();
	while (begin != end)
	{
		serializeSingleObject(*begin, file);
		++begin;
	}
	closeFile(file);
}
