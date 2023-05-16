#include "Measure.h"

Measure Measure::operator+(const Measure& other) const
{
	return Measure(this->value + other.getValue(this->exponent), this->exponent);
}

void Measure::operator+=(const Measure& other)
{
	this->value = (this->value + other.getValue(this->exponent));
}

Measure Measure::operator-(const Measure& other) const
{
	return Measure(this->value - other.getValue(this->exponent), this->exponent);
}

void Measure::operator-=(const Measure& other)
{
	this->value = (this->value - other.getValue(this->exponent));
}

Measure Measure::operator*(const Measure& other) const
{
	Measure temp(this->value * other.value, this->exponent + other.exponent);
	return Measure(temp.getValue(this->exponent), this->exponent);
}

Measure Measure::operator/(const Measure& other) const
{
	Measure temp(this->value / other.value, static_cast<int8_t>((this->exponent - other.exponent)));
	return Measure(temp.getValue(this->exponent), this->exponent);
}

Measure::operator float() const
{
	return this->getValue(1);
}

void Measure::setValue(float value, int8_t exponent)
{
	this->value = value;
	this->exponent = exponent;
}

float Measure::getValue(int8_t desiredExponent) const
{
	int multiplier = desiredExponent - this->exponent;
	return static_cast<float>(this->value / std::pow(10.0f, multiplier));
}
