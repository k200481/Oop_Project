#pragma once
#include <math.h>

template<typename T>
class Vec2
{
	Vec2()
	{}
	Vec2( T x, T y )
		:
		x(x),
		y(y)
	{}

	// addition/subtraction of two vectors
	Vec2 operator+(const Vec2& rhs) {
		return Vec2(x + rhs.x, y + rhs.y);
	}
	Vec2 operator-(const Vec2& rhs) {
		return Vec2(x - rhs.x, y - rhs.y);
	}
	Vec2& operator+=(const Vec2& rhs) {
		return *this = *this + rhs;
	}
	Vec2& operator-=(const Vec2& rhs) {
		return *this = *this - rhs;
	}

	// multiplication/division of vector with scalar
	Vec2 operator*(T rhs) {
		return Vec2(x * rhs, y * rhs);
	}
	Vec2 operator/(T rhs) {
		return Vec2(x / rhs, y / rhs);
	}
	Vec2& operator*=(T rhs) {
		return *this = *this * rhs;
	}
	Vec2& operator/=(T rhs) {
		return *this = *this / rhs;
	}

	double MagnitudeSquared() {
		return double(x) * double(x) + double(y) * double(y);
	}
	double Magnitude() {
		return sqrt(MagnitudeSquared());
	}

	Vec2 UnitVector() {
		return *this / T(Magnitude());
	}
	Vec2& ConvertToUnitVector() {
		return *this = UnitVector();
	}
public:
	// this is very simple data, no need to keep it private
	T x = T(0);
	T y = T(0);
};
