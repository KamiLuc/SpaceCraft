#pragma once

#include <cmath>
#include <ostream>

class PhysicalUnit
{
public:
	PhysicalUnit();
	PhysicalUnit(float val, int exponent);
	PhysicalUnit(float val);

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
	PhysicalUnit convertTo(int newExponent) const;
	PhysicalUnit getSqrt() const;
	PhysicalUnit getSquared() const;
	operator float() const;

	void print(std::ostream& os) const;
	void normalize();
	float getBase() const;
	float getValue() const;
	float* getBasePtr();
	int getExponent() const;
	int* getExponentPtr();

private:
	float base;
	int exponent;
};

