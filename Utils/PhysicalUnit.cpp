#include "PhysicalUnit.h"

PhysicalUnit::PhysicalUnit()
	: PhysicalUnit(0, 0)
{
}

PhysicalUnit::PhysicalUnit(float val, int exponent)
	: base(val)
	, exponent(exponent)
{
}

PhysicalUnit::PhysicalUnit(float val)
	: PhysicalUnit(val, 0)
{
}

PhysicalUnit PhysicalUnit::convertTo(int newExponent) const
{
	float newBase = base * static_cast<float>(std::pow(10, exponent - newExponent));
	return PhysicalUnit(newBase, newExponent);
}

PhysicalUnit PhysicalUnit::operator-(const PhysicalUnit& other) const
{
	int commonExponent = std::max(exponent, other.exponent);
	float newBase = (base * static_cast<float>(std::pow(10, exponent - commonExponent))) -
		(other.base * static_cast<float>(std::pow(10, other.exponent - commonExponent)));
	return PhysicalUnit(newBase, commonExponent);
}

PhysicalUnit& PhysicalUnit::operator-=(const PhysicalUnit& other)
{
	int commonExponent = std::max(exponent, other.exponent);
	float newBase = (base * static_cast<float>(std::pow(10, exponent - commonExponent))) -
		(other.base * static_cast<float>(std::pow(10, other.exponent - commonExponent)));
	this->exponent = commonExponent;
	this->base = newBase;
	return *this;
}

PhysicalUnit PhysicalUnit::operator+(const PhysicalUnit& other) const
{
	int commonExponent = std::max(exponent, other.exponent);
	float newBase = (base * static_cast<float>(std::pow(10, exponent - commonExponent))) +
		(other.base * static_cast<float>(std::pow(10, other.exponent - commonExponent)));
	return PhysicalUnit(newBase, commonExponent);
}

PhysicalUnit& PhysicalUnit::operator+=(const PhysicalUnit& other)
{
	int commonExponent = std::max(exponent, other.exponent);;
	float newBase = (base * static_cast<float>(std::pow(10, exponent - commonExponent))) +
		(other.base * static_cast<float>(std::pow(10, other.exponent - commonExponent)));
	this->exponent = commonExponent;
	this->base = newBase;
	return *this;
}

PhysicalUnit PhysicalUnit::operator/(const PhysicalUnit& other) const
{
	float newBase = base / other.base;
	int newExponent = exponent - other.exponent;
	return PhysicalUnit(newBase, newExponent);
}

PhysicalUnit& PhysicalUnit::operator/=(const PhysicalUnit& other)
{
	base /= other.base;
	exponent -= other.exponent;
	return *this;
}

PhysicalUnit PhysicalUnit::operator*(const PhysicalUnit& other) const
{
	float newBase = base * other.base;
	int newExponent = exponent + other.exponent;
	return PhysicalUnit(newBase, newExponent);
}

PhysicalUnit& PhysicalUnit::operator*=(const PhysicalUnit& other)
{
	base *= other.base;
	exponent += other.exponent;
	return *this;
}

PhysicalUnit PhysicalUnit::operator*(float other) const
{
	return PhysicalUnit(base * other, exponent);
}

PhysicalUnit& PhysicalUnit::operator*=(float other)
{
	base *= other;
	return *this;
}

PhysicalUnit PhysicalUnit::getSqrt() const
{
	if (exponent % 2 == 0)
	{
		return PhysicalUnit(std::sqrt(base), exponent / 2);
	}
	else
	{
		return this->convertTo(exponent - 1).getSqrt();
	}
}

PhysicalUnit PhysicalUnit::getSquared() const
{
	return PhysicalUnit(base * base, exponent * 2);
}

PhysicalUnit::operator float() const
{
	return getValue();
}

void PhysicalUnit::normalize()
{
	while (base >= 10.0)
	{
		base /= 10.0;
		exponent++;
	}
	while (base < 1.0)
	{
		base *= 10.0;
		exponent--;
	}
}

float PhysicalUnit::getBase() const
{
	return base;
}

float* PhysicalUnit::getBasePtr()
{
	return &base;
}

int PhysicalUnit::getExponent() const
{
	return exponent;
}

int* PhysicalUnit::getExponentPtr()
{
	return &exponent;
}

void PhysicalUnit::serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version)
{
	outputArchive& base;
	outputArchive& exponent;
}

void PhysicalUnit::serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version)
{
	inputArchive& base;
	inputArchive& exponent;
}

float PhysicalUnit::getValue() const
{
	return base * static_cast<float>(std::pow(10, exponent));
}

void PhysicalUnit::print(std::ostream& os) const
{
	os << "Base:     " << base << "\n";
	os << "Exponent: " << exponent << "\n";
	os << "Value:    " << getValue() << "\n";
}
