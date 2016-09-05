#pragma once
#include "Types.hpp"
#include <math.h>

//=============================================================================
// Math constants.
//=============================================================================

// PI values.
#define MATH_PI_INV			0.3183098861837906
#define MATH_PI_2			1.5707963267948966
#define MATH_PI				3.1415926535897932
#define MATH_3_PI_2			4.7123889803846898
#define MATH_2_PI			6.2831853071795864

// Angle conversion.
#define MATH_DEG_TO_RAD		0.0174532925199432
#define MATH_RAD_TO_DEG		57.295779513082320

// Epsilon values.
#define MATH_EPSILON_LARGE 0.001
#define MATH_EPSILON_SMALL 0.00000001

namespace Math {

//=============================================================================
// Templated utility functions.
//=============================================================================

// Clamps x between the min and max value.
template <typename Type>
CONSTEXPR Type Clamp(Type const x, Type const min, Type const max) {
	return x < min ? min : (x < max ? x : max);
}

// Returns the maximum of x and y.
template <typename Type>
CONSTEXPR Type Max(Type const x, Type const y) {
	return x < y ? y : x;
}

// Returns the minimum of x and y.
template <typename Type>
CONSTEXPR Type Min(Type const x, Type const y) {
	return y < x ? y : x;
}

// Returns the squared value of x.
template <typename Type>
CONSTEXPR Type Square(Type const x) {
	return x * x;
}

//=============================================================================
// Angle functions.
//=============================================================================

// Returns the given angle expressed in degrees to radians.
CONSTEXPR f64 DegToRad(f64 const angle) {
	return angle * MATH_DEG_TO_RAD;
}

// Returns the given angle expressed in radians to degrees.
CONSTEXPR f64 RadToDeg(f64 const angle) {
	return angle * MATH_RAD_TO_DEG;
}

// Wraps x between [0, max).
FORCEINLINE f64 WrapMax(f64 const x, f64 const max) {
	return fmod(max + fmod(x, max), max);
}

// Wraps x between [min, max).
FORCEINLINE f64 WrapMinMax(f64 const x, f64 const min, f64 const max) {
	return min + WrapMax(x - min, max - min);
}

// Wraps an angle expressed in degrees between [-180, 180).
FORCEINLINE f64 WrapAngleDeg(f64 const angle) {
	return WrapMinMax(angle, -180.0, 180.0);
}

// Wraps an angle expressed in radians between [-PI, PI].
FORCEINLINE f64 WrapAngleRad(f64 const angle) {
	return atan2(sin(angle), cos(angle));
}

//=============================================================================
// Rounding functions.
//=============================================================================

// Rounds an i32 up to the nearest factor given.
CONSTEXPR i32 RoundI32(i32 const x, i32 const factor) {
	return x + factor - 1 - (x - 1) % factor;
}

// Rounds an i32 up to the nearest power of two.
FORCEINLINE i32 RoundPow2(i32 x) {
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x++;

	return x;
}

// Saturates a value between 0.0 and 1.0.
CONSTEXPR f32 Saturate(f32 const x) {
	return x < 0.0f ? 0.0f : (x < 1.0f ? x : 1.0f);
}

}
