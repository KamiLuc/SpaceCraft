#pragma once

#include <vector>
#include <ostream>

template<typename T>
class CircularVector {
public:
	CircularVector(size_t maxSize);
	void push(const T& value);

	size_t getMaxSize() const;
	T* getData();
	void print(std::ostream& os);

protected:
	std::vector<T> data;
	std::size_t maxSize;
};

template<typename T>
inline CircularVector<T>::CircularVector(size_t maxSize) : maxSize(maxSize) {}

template<typename T>
inline void CircularVector<T>::push(const T& value)
{
	if (data.size() < maxSize) {
		data.emplace_back(value);
	}
	else {
		std::memcpy(data.data(), data.data() + 1, sizeof(value) * (maxSize - 1));
		data.back() = value;
	}
}

template<typename T>
inline size_t CircularVector<T>::getMaxSize() const
{
	return maxSize;
}

template<typename T>
inline T* CircularVector<T>::getData()
{
	return data.data();
}

template<typename T>
inline void CircularVector<T>::print(std::ostream& os)
{
	os << "maxSize: " << maxSize << "\n";

	for (const auto& el : data) {
		os << el << " ";
	}

	os << "\n";
}

