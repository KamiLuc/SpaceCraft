#pragma once

#include <cmath>

class PhysicalUnit
{
public:
    PhysicalUnit();
    PhysicalUnit(float val, int exponent);
    PhysicalUnit convertTo(int newExponent) const;

    PhysicalUnit operator-(const PhysicalUnit& other) const;
    void operator-=(const PhysicalUnit& other);

    PhysicalUnit operator+(const PhysicalUnit& other) const;
    void operator+=(const PhysicalUnit& other);

    PhysicalUnit operator/(const PhysicalUnit& other) const;
    void operator/=(const PhysicalUnit& other);

    PhysicalUnit operator*(const PhysicalUnit& other) const;
    void operator*=(const PhysicalUnit& other);

    void normalize();
    float getValue() const;

private:
    float value;
    int exponent;
};

