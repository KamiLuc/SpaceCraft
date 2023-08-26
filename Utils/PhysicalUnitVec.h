#pragma once

#include "PhysicalUnit.h"

#include <array>

template <int Elements>
class PhysicalUnitVec
{
public:
    PhysicalUnitVec(const std::array<PhysicalUnit, Elements>& values) : vec(values) {}
    PhysicalUnitVec(const PhysicalUnit& value);
    PhysicalUnitVec();

    PhysicalUnitVec operator+(const PhysicalUnitVec& other) const {
        PhysicalUnitVec result(*this);
        for (size_t i = 0; i < Elements; ++i) {
            result.vec[i] = vec[i] + other.vec[i];
        }
        return result;
    }

    PhysicalUnitVec operator-(const PhysicalUnitVec& other) const {
        PhysicalUnitVec result(*this);
        for (size_t i = 0; i < Elements; ++i) {
            result.vec[i] = vec[i] - other.vec[i];
        }
        return result;
    }

    PhysicalUnitVec operator*(const PhysicalUnitVec& other) const {
        PhysicalUnitVec result(*this);
        for (size_t i = 0; i < Elements; ++i) {
            result.vec[i] = vec[i] * other.vec[i];
        }
        return result;
    }

    PhysicalUnitVec operator/(const PhysicalUnitVec& other) const {
        PhysicalUnitVec result(*this);
        for (size_t i = 0; i < Elements; ++i) {
            result.vec[i] = vec[i] / other.vec[i];
        }
        return result;
    }

    void normalize() {
        for (auto& el : vec) {
            el.normalize();
        }
    }


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
