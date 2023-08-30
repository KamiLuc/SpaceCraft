#pragma once

#include <cmath>
#include <ostream>

class PhysicalUnit
{
public:
    PhysicalUnit();
    PhysicalUnit(float val, int exponent);
    PhysicalUnit(float val);
    PhysicalUnit convertTo(int newExponent) const;

    PhysicalUnit operator-(const PhysicalUnit& other) const;
    PhysicalUnit& operator-=(const PhysicalUnit& other);

    PhysicalUnit operator+(const PhysicalUnit& other) const;
    PhysicalUnit& operator+=(const PhysicalUnit& other);

    PhysicalUnit operator/(const PhysicalUnit& other) const;
    PhysicalUnit& operator/=(const PhysicalUnit& other);

    PhysicalUnit operator*(const PhysicalUnit& other) const;
    PhysicalUnit& operator*=(const PhysicalUnit& other);
    PhysicalUnit operator*(float other) const;
    PhysicalUnit& operator*=(float other);

    PhysicalUnit getSqrt() const;
    PhysicalUnit getSquared() const;
    operator float() const;

    void normalize();
    float getBase() const;
    float* getBasePtr();
    int getExponent() const;
    int* getExponentPtr();
    float getValue() const;

    void print(std::ostream& os) const;

private:
    float base;
    int exponent;
};

