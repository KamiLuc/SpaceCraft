#pragma once

#include "AppFramework/Serializer/Serializable.h"
#include "PhysicalUnit.h"
#include "glm/glm.hpp"
#include "glm/common.hpp"

#include <array>
#include <stdexcept>

template <int Elements>
class PhysicalUnitVec : public Serializable
{
public:
	PhysicalUnitVec(const std::array<PhysicalUnit, Elements>& values) : vec(values) {}
	PhysicalUnitVec(const PhysicalUnit& value);
	PhysicalUnitVec(const glm::vec<3, float>& glmVec);
	PhysicalUnitVec();

	PhysicalUnitVec operator+(const PhysicalUnitVec& other) const;
	PhysicalUnitVec& operator+=(const PhysicalUnitVec& other);
	PhysicalUnitVec operator+(const PhysicalUnit& other) const;
	PhysicalUnitVec& operator+=(const PhysicalUnit& other);
	PhysicalUnitVec operator-(const PhysicalUnitVec& other) const;
	PhysicalUnitVec& operator-=(const PhysicalUnitVec& other);
	PhysicalUnitVec operator*(const PhysicalUnitVec& other) const;
	PhysicalUnitVec& operator*=(const PhysicalUnitVec& other);
	PhysicalUnitVec operator*(const PhysicalUnit& other) const;
	PhysicalUnitVec& operator*=(const PhysicalUnit& other);
	PhysicalUnitVec operator/(const PhysicalUnitVec& other) const;
	PhysicalUnitVec& operator/=(const PhysicalUnitVec& other);
	PhysicalUnitVec operator/(const PhysicalUnit& other) const;
	PhysicalUnitVec& operator/=(const PhysicalUnit& other);
	PhysicalUnit& operator[](size_t index);
	const PhysicalUnit& operator[](size_t index) const;

	void normalize();
	void print(std::ostream& stream);
	glm::vec<Elements, float> getGlmVec() const;
	std::array<PhysicalUnit, Elements>& getData();
	PhysicalUnit getLength() const;
	PhysicalUnitVec getNormalized() const;

	void serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version) override;
	void serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version) override;

private:
	std::array<PhysicalUnit, Elements> vec;
};

template<int Elements>
inline PhysicalUnitVec<Elements>::PhysicalUnitVec(const PhysicalUnit& value)
{
	for (size_t i = 0; i < Elements; ++i)
	{
		vec[i] = value;
	}
}

template<int Elements>
inline PhysicalUnitVec<Elements>::PhysicalUnitVec(const glm::vec<3, float>& glmVec)
{
	for (auto i = 0; i < Elements; ++i)
	{
		vec[i] = PhysicalUnit(glmVec[i], 0);
	}
}

template<int Elements>
inline PhysicalUnitVec<Elements>::PhysicalUnitVec()
{
	for (size_t i = 0; i < Elements; ++i)
	{
		vec[i] = PhysicalUnit();
	}
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::operator+(const PhysicalUnitVec& other) const
{
	PhysicalUnitVec result(*this);
	for (auto i = 0; i < Elements; ++i)
	{
		result.vec[i] += other.vec[i];
	}
	return result;
}

template<int Elements>
inline PhysicalUnitVec<Elements>& PhysicalUnitVec<Elements>::operator+=(const PhysicalUnitVec& other)
{
	for (size_t i = 0; i < Elements; ++i)
	{
		vec[i] += other.vec[i];
	}
	return *this;
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::operator+(const PhysicalUnit& other) const
{
	PhysicalUnitVec result(*this);
	for (size_t i = 0; i < Elements; ++i)
	{
		result.vec[i] += other;
	}
	return result;
}

template<int Elements>
inline PhysicalUnitVec<Elements>& PhysicalUnitVec<Elements>::operator+=(const PhysicalUnit& other)
{
	for (size_t i = 0; i < Elements; ++i)
	{
		vec[i] += other;
	}
	return *this;
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::operator-(const PhysicalUnitVec& other) const
{
	PhysicalUnitVec result(*this);
	for (size_t i = 0; i < Elements; ++i)
	{
		result.vec[i] -= other.vec[i];
	}
	return result;
}

template<int Elements>
inline PhysicalUnitVec<Elements>& PhysicalUnitVec<Elements>::operator-=(const PhysicalUnitVec& other)
{
	for (size_t i = 0; i < Elements; ++i)
	{
		vec[i] -= other.vec[i];
	}
	return *this;
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::operator*(const PhysicalUnitVec& other) const
{
	PhysicalUnitVec result(*this);
	for (size_t i = 0; i < Elements; ++i)
	{
		result.vec[i] *= other.vec[i];
	}
	return result;
}

template<int Elements>
inline PhysicalUnitVec<Elements>& PhysicalUnitVec<Elements>::operator*=(const PhysicalUnitVec& other)
{
	*this = *this * other;
	return *this;
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::operator*(const PhysicalUnit& other) const
{
	PhysicalUnitVec result(*this);
	for (size_t i = 0; i < Elements; ++i)
	{
		result.vec[i] *= other;
	}
	return result;
}

template<int Elements>
inline PhysicalUnitVec<Elements>& PhysicalUnitVec<Elements>::operator*=(const PhysicalUnit& other)
{

	for (size_t i = 0; i < Elements; ++i)
	{
		vec[i] *= other;
	}
	return *this;
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::operator/(const PhysicalUnitVec& other) const
{
	PhysicalUnitVec result(*this);
	for (size_t i = 0; i < Elements; ++i)
	{
		result.vec[i] /= other.vec[i];
	}
	return result;
}

template<int Elements>
inline PhysicalUnitVec<Elements>& PhysicalUnitVec<Elements>::operator/=(const PhysicalUnitVec& other)
{
	for (size_t i = 0; i < Elements; ++i)
	{
		vec[i] /= other.vec[i];
	}
	return *this;
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::operator/(const PhysicalUnit& other) const
{
	PhysicalUnitVec result(*this);
	for (size_t i = 0; i < Elements; ++i)
	{
		result.vec[i] /= other;
	}
	return result;
}

template<int Elements>
inline PhysicalUnitVec<Elements>& PhysicalUnitVec<Elements>::operator/=(const PhysicalUnit& other)
{
	*this = *this / other;
	return *this;
}

template<int Elements>
inline PhysicalUnit& PhysicalUnitVec<Elements>::operator[](size_t index)
{
	if (index < 0 || index >= Elements)
	{
		throw std::out_of_range("Index out of range");
	}
	return vec[index];
}

template<int Elements>
inline const PhysicalUnit& PhysicalUnitVec<Elements>::operator[](size_t index) const
{
	if (index < 0 || index >= Elements)
	{
		throw std::out_of_range("Index out of range");
	}
	return vec[index];
}

template<int Elements>
inline glm::vec<Elements, float> PhysicalUnitVec<Elements>::getGlmVec() const
{
	glm::vec<Elements, float> result {};
	for (auto i = 0; i < Elements; ++i)
	{
		result[i] = static_cast<float>(vec[i].getValue());
	}
	return result;
}

template<int Elements>
inline std::array<PhysicalUnit, Elements>& PhysicalUnitVec<Elements>::getData()
{
	return vec;
}

template<int Elements>
inline void PhysicalUnitVec<Elements>::normalize()
{
	for (auto& el : vec)
	{
		el.normalize();
	}
}

template<int Elements>
inline void PhysicalUnitVec<Elements>::print(std::ostream& stream)
{
	for (size_t i = 0; i < Elements; ++i)
	{
		stream << "Index: " << i << "\n";
		vec[i].print(stream);
	}
}

template<int Elements>
inline PhysicalUnit PhysicalUnitVec<Elements>::getLength() const
{
	PhysicalUnit squaredLength(0.0f, 0);
	for (const PhysicalUnit& component : vec)
	{
		squaredLength += component.getSquared();
	}
	return squaredLength.getSqrt();
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::getNormalized() const
{
	PhysicalUnitVec<Elements> normalizedVec;
	auto length = getLength();

	if (length.getValue() == 0.0f)
	{
		return *this;
	}

	for (size_t i = 0; i < Elements; ++i)
	{
		normalizedVec[i] = vec[i] / length;
	}

	return normalizedVec;
}

template<int Elements>
inline void PhysicalUnitVec<Elements>::serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version)
{
	for (auto i = 0; i < Elements; ++i)
	{
		outputArchive& vec[i];
	}
}

template<int Elements>
inline void PhysicalUnitVec<Elements>::serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version)
{
	for (auto i = 0; i < Elements; ++i)
	{
		inputArchive& vec[i];
	}
}
