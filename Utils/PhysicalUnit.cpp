#include "PhysicalUnit.h"


PhysicalUnit::PhysicalUnit()
    : PhysicalUnit(0,0)
{
}

PhysicalUnit::PhysicalUnit(float val, int exponent)
    : value(val)
    , exponent(exponent)
{
}

PhysicalUnit PhysicalUnit::convertTo(int newExponent) const
{
    float newValue = value * static_cast<float>(std::pow(10, exponent - newExponent));
    return PhysicalUnit(newValue, newExponent);
}

PhysicalUnit PhysicalUnit::operator-(const PhysicalUnit& other) const
{
    int commonPower = std::max(exponent, other.exponent);
    float newValue = (value * static_cast<float>(std::pow(10, exponent - commonPower))) -
        (other.value * static_cast<float>(std::pow(10, other.exponent - commonPower)));
    return PhysicalUnit(newValue, commonPower);
}

void PhysicalUnit::operator-=(const PhysicalUnit& other)
{
    *this = *this - other;
}

PhysicalUnit PhysicalUnit::operator+(const PhysicalUnit& other) const
{
    int commonPower = std::max(exponent, other.exponent);
    float newValue = (value * static_cast<float>(std::pow(10, exponent - commonPower))) +
        (other.value * static_cast<float>(std::pow(10, other.exponent - commonPower)));
    return PhysicalUnit(newValue, commonPower);
}

void PhysicalUnit::operator+=(const PhysicalUnit& other)
{
    *this = *this + other;
}

PhysicalUnit PhysicalUnit::operator/(const PhysicalUnit& other) const
{
    float newValue = value / other.value;
    int newPower = exponent - other.exponent;
    return PhysicalUnit(newValue, newPower);
}

void PhysicalUnit::operator/=(const PhysicalUnit& other)
{
    *this = *this / other;
}

PhysicalUnit PhysicalUnit::operator*(const PhysicalUnit& other) const
{
    float newValue = value * other.value;
    int newPower = exponent + other.exponent;
    return PhysicalUnit(newValue, newPower);
}

void PhysicalUnit::operator*=(const PhysicalUnit& other)
{
    *this = *this * other;
}

void PhysicalUnit::normalize()
{
    while (value >= 10.0) {
        value /= 10.0;
        exponent++;
    }
    while (value < 1.0) {
        value *= 10.0;
        exponent--;
    }
}

float PhysicalUnit::getValue() const
{
    return value * static_cast<float>(std::pow(10, exponent));
}
