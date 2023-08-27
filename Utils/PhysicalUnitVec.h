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

    glm::vec<Elements, float> getGlmVec() const;
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

template<int Elements>
inline glm::vec<Elements, float> PhysicalUnitVec<Elements>::getGlmVec() const
{
    glm::vec<Elements, float> result{};
    for (auto i = 0; i < Elements; i++) {
        result[i] = static_cast<float>(vec[i].getValue());
    }
    return result;
}
