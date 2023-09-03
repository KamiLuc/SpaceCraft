#pragma once

#include <vector>
#include <ostream>
#include <iterator>
#include <stdexcept>

template<typename T>
class CircularVector
{
public:
	CircularVector(size_t size);
	size_t getMaxSize() const;
	size_t getActualSize() const;
	T* getData();
	void push(const T& value);
	void setMaxSize(size_t size);
	void print(std::ostream& os);
	void clear();

protected:
	std::vector<T> data;
	std::size_t maxSize;
	std::vector<T>::iterator actualDataBegin; 
	std::vector<T>::iterator actualDataEnd;
};

template<typename T>
inline CircularVector<T>::CircularVector(size_t maxSize)
	: maxSize(maxSize)
	, data(maxSize * 2)
	, actualDataEnd(data.begin())
	, actualDataBegin(data.begin())
{
	if (maxSize < 0)
	{
		throw std::runtime_error("Negative size is not allowed.");
	}

	data.resize(maxSize * 2);
	actualDataEnd = data.begin();
	actualDataBegin = data.begin();
}

template<typename T>
inline void CircularVector<T>::setMaxSize(size_t maxSize)
{
	if (maxSize < 0)
	{
		throw std::runtime_error("Negative size is not allowed.");
	}

	auto acutalSize = getActualSize();

	if (maxSize > acutalSize)
	{
		this->maxSize = maxSize;
		data.resize(maxSize);
	}
	else if (maxSize < acutalSize)
	{
		this->maxSize = maxSize;
		std::vector<T> newData(maxSize * 2);
		std::copy(actualDataEnd - maxSize, actualDataEnd, newData.begin());
		data = std::move(newData);
		actualDataBegin = data.begin();
		actualDataEnd = actualDataBegin + maxSize;
	}
}

template<typename T>
inline size_t CircularVector<T>::getMaxSize() const
{
	return maxSize;
}

template<typename T>
inline size_t CircularVector<T>::getActualSize() const
{
	return std::distance(actualDataBegin, actualDataEnd);
}

template<typename T>
inline T* CircularVector<T>::getData()
{
	return &*actualDataBegin;
}

template<typename T>
inline void CircularVector<T>::push(const T& value)
{
	auto acutalSize = getActualSize();

	if (acutalSize == maxSize)
	{
		if (actualDataEnd != data.end())
		{
			++actualDataBegin;
			*actualDataEnd = value;
			++actualDataEnd;
		}
		else
		{
			std::copy(++actualDataBegin, actualDataEnd, data.begin());
			actualDataBegin = data.begin();
			actualDataEnd = actualDataBegin + (maxSize - 1);
			*actualDataEnd = value;
			++actualDataEnd;
		}
	}
	else if (acutalSize < maxSize)
	{
		*actualDataEnd = value;
		++actualDataEnd;
	}
}

template<typename T>
inline void CircularVector<T>::print(std::ostream& os)
{
	os << "maxSize:    " << maxSize << "\n";
	os << "actualSize: " << getActualSize() << "\n";

	for (const auto& el : std::ranges::subrange(actualDataBegin, actualDataEnd))
	{
		os << el << " ";
	}

	os << "\n";
}

template<typename T>
inline void CircularVector<T>::clear()
{
	data.clear();
}
