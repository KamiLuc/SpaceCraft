#pragma once
#include <concepts>
#include <cmath>

class Measure
{
public:
	Measure(float value, int8_t exponent) : value(value), exponent(exponent) {}
	Measure(float value) : Measure(value, 1) {};

	Measure operator+(const Measure& other) const;
	void operator+=(const Measure& other);

	Measure operator-(const Measure& other) const;
	void operator-=(const Measure& other);

	Measure operator*(const Measure& other) const;

	Measure operator/(const Measure& other) const;

	operator float() const;

	void setValue(float value, int8_t exponent);

	float getValue(int8_t desiredExponent) const;

private:
	float value;
	int8_t exponent;
};
