#pragma once
#pragma once

#include <concepts>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

template<typename T>
concept PositiveInt = std::is_integral_v<T> && std::is_unsigned_v<T>;

template<unsigned int elements>
class Measure
{
public:
	Measure(glm::vec<elements, float> values, int exponent) : values(values), exponent(exponent) {}
	Measure(glm::vec<elements, float> values) : Measure(values, 0) {}
	Measure(float value, int exponent) : Measure(glm::vec<elements, float>(value), exponent) {}
	Measure(float value) : Measure(value, 0) {}

	Measure<elements> operator+(const Measure& other) const;
	void operator+=(const Measure& other);

	Measure<elements> operator-(const Measure& other) const;
	void operator-=(const Measure& other);

	Measure<elements> operator*(const Measure& other) const;
	void operator*= (const Measure& other);

	Measure<elements> operator/(const Measure& other) const;
	void operator/= (const Measure& other);

	operator glm::vec<elements, float>() {
		return getGlmVec();
	}

	glm::vec<elements, float> getGlmVec() const;
	glm::vec<elements, float> getValuesInDesiredExponent(int desiredExponent) const;

	float* getValuesPtr();
	int* getExponentPtr();
	void normalize();

private:
	glm::vec<elements, float> values;
	int exponent;
};

template<unsigned int elements>
inline Measure<elements> Measure<elements>::operator+(const Measure& other) const
{
	return Measure<elements>(this->values + other.getValuesInDesiredExponent(this->exponent), this->exponent);
}

template<unsigned int elements>
inline void Measure<elements>::operator+=(const Measure& other)
{
	this->values += other.getValuesInDesiredExponent(this->exponent);
}

template<unsigned int elements>
inline Measure<elements> Measure<elements>::operator-(const Measure& other) const
{
	return Measure<elements>(this->values - other.getValuesInDesiredExponent(this->exponent), this->exponent);
}

template<unsigned int elements>
inline void Measure<elements>::operator-=(const Measure& other)
{
	this->values -= other.getValuesInDesiredExponent(this->exponent);
}

template<unsigned int elements>
inline Measure<elements> Measure<elements>::operator*(const Measure& other) const
{
	Measure<elements> temp(this->values * other.values, this->exponent + other.exponent);
	return Measure(temp.getValuesInDesiredExponent(this->exponent), this->exponent);
}

template<unsigned int elements>
inline void Measure<elements>::operator*=(const Measure& other)
{
	this->values = Measure(*this * other).values;
}

template<unsigned int elements>
inline Measure<elements> Measure<elements>::operator/(const Measure& other) const
{
	Measure<elements> temp(this->values / other.values, this->exponent - other.exponent);
	return Measure(temp.getValuesInDesiredExponent(this->exponent), this->exponent);
}

template<unsigned int elements>
inline void Measure<elements>::operator/=(const Measure& other)
{
	this->values = Measure(*this / other).values;
}

template<unsigned int elements>
glm::vec<elements, float> Measure<elements>::getGlmVec() const
{
	glm::vec<elements, float> result{};
	for (unsigned int i = 0; i < elements; i++) {
		result[i] = static_cast<float>(this->values[i] * std::pow(10, this->exponent));
	}
	return result;
}

template<unsigned int elements>
inline glm::vec<elements, float> Measure<elements>::getValuesInDesiredExponent(int desiredExponent) const
{
	auto result = values;
	auto p = std::pow(10, desiredExponent - this->exponent);
	for (unsigned int i = 0; i < elements; i++) {
		result[i] = (result[i] / static_cast<float>(p));
	}
	return result;
}

template<>
inline float* Measure<1>::getValuesPtr()
{
	return &values.x;
}

template<unsigned int elements>
inline float* Measure<elements>::getValuesPtr()
{
	return glm::value_ptr(values);
}

template<unsigned int elements>
inline int* Measure<elements>::getExponentPtr()
{
	return &exponent;
}

template<unsigned int elements>
inline void Measure<elements>::normalize()
{
	while (true) {
		unsigned int tooBig = 0;
		unsigned int tooSmall = 0;

		for (unsigned int i = 0; i < elements; ++i) {
			if ((values[i] > 10.0f || values[i] < -10.0f) && values[i] != 0) {
				++tooBig;
				continue;
			}

			else if ((values[i] < 0.1f && values[i] > 0.0f) || (values[i] > -0.1f && values[i] < 0.0f)) {
				++tooSmall;
				continue;
			}

			else {
				return;
			}
		}

		if (tooBig == elements) {
			for (unsigned int i = 0; i < elements; ++i) {
				values[i] /= 10.0f;
			}
			++exponent;
		}

		else if (tooSmall == elements) {
			for (unsigned int i = 0; i < elements; ++i) {
				values[i] *= 10.0f;
			}
			--exponent;
		}

		else {
			return;
		}
	}
}

