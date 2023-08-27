#pragma once

#include "PhysicalUnit.h"
#include "glm/glm.hpp"

#include <array>

template <int Elements>
class PhysicalUnitVec
{
public:
    PhysicalUnitVec(const std::array<PhysicalUnit, Elements>& values) : vec(values) {}
    PhysicalUnitVec(const PhysicalUnit& value);
    PhysicalUnitVec();

    PhysicalUnitVec operator+(const PhysicalUnitVec& other) const;
    PhysicalUnitVec& operator+=(const PhysicalUnitVec& other);

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

    glm::vec<Elements, float> getGlmVec() const;
    void normalize();

private:
	std::array<PhysicalUnit, Elements> vec;
};

template<int Elements>
inline PhysicalUnitVec<Elements>::PhysicalUnitVec(const PhysicalUnit& value)
{
    for (size_t i = 0; i < Elements; ++i) {
        vec[i] = value;
    }
}

template<int Elements>
inline PhysicalUnitVec<Elements>::PhysicalUnitVec()
{
    for (size_t i = 0; i < Elements; ++i) {
        vec[i] = PhysicalUnit();
    }
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::operator+(const PhysicalUnitVec& other) const
{
    PhysicalUnitVec result(*this);
    for (size_t i = 0; i < Elements; ++i) {
        result.vec[i] += other.vec[i];
    }
    return result;
}

template<int Elements>
inline PhysicalUnitVec<Elements>& PhysicalUnitVec<Elements>::operator+=(const PhysicalUnitVec& other)
{
    *this = *this + other;
    return *this;
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::operator-(const PhysicalUnitVec& other) const
{
    PhysicalUnitVec result(*this);
    for (size_t i = 0; i < Elements; ++i) {
        result.vec[i] -= other.vec[i];
    }
    return result;
}

template<int Elements>
inline PhysicalUnitVec<Elements>& PhysicalUnitVec<Elements>::operator-=(const PhysicalUnitVec& other)
{
    *this = *this - other;
    return *this;
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::operator*(const PhysicalUnitVec& other) const
{
    PhysicalUnitVec result(*this);
    for (size_t i = 0; i < Elements; ++i) {
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
    for (size_t i = 0; i < Elements; ++i) {
        result.vec[i] *= other;
    }
    return result;
}

template<int Elements>
inline PhysicalUnitVec<Elements>& PhysicalUnitVec<Elements>::operator*=(const PhysicalUnit& other)
{
    
    *this = *this * other;
    return *this;
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::operator/(const PhysicalUnitVec& other) const
{
    PhysicalUnitVec result(*this);
    for (size_t i = 0; i < Elements; ++i) {
        result.vec[i] /= other.vec[i];
    }
    return result;
}

template<int Elements>
inline PhysicalUnitVec<Elements>& PhysicalUnitVec<Elements>::operator/=(const PhysicalUnitVec& other)
{
    *this = *this / other;
    return *this;
}

template<int Elements>
inline PhysicalUnitVec<Elements> PhysicalUnitVec<Elements>::operator/(const PhysicalUnit& other) const
{
    PhysicalUnitVec result(*this);
    for (size_t i = 0; i < Elements; ++i) {
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
inline glm::vec<Elements, float> PhysicalUnitVec<Elements>::getGlmVec() const
{
    glm::vec<Elements, float> result{};
    for (auto i = 0; i < Elements; i++) {
        result[i] = static_cast<float>(vec[i].getValue());
    }
    return result;
}

template<int Elements>
inline void PhysicalUnitVec<Elements>::normalize()
{
    for (auto& el : vec) {
        el.normalize();
    }
}