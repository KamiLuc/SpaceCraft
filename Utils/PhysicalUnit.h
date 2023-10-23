#pragma once

#include "AppFramework/Serializer/Serializable.h"

#include <cmath>
#include <ostream>
#include <string>
#include <sstream>

class PhysicalUnit : public Serializable
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

	void serialize(boost::archive::text_oarchive& outputArchive, const unsigned int version) override;
	void serialize(boost::archive::text_iarchive& inputArchive, const unsigned int version) override;

private:
	float base;
	int exponent;
};
