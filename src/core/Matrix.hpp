#pragma once
#include "Types.hpp"

//=============================================================================
// mat4 operators.
//=============================================================================

FORCEINLINE void operator+=(mat4& m1, f32 const k) {
	m1._11 += k;
	m1._12 += k;
	m1._13 += k;
	m1._14 += k;

	m1._21 += k;
	m1._22 += k;
	m1._23 += k;
	m1._24 += k;

	m1._31 += k;
	m1._32 += k;
	m1._33 += k;
	m1._34 += k;

	m1._41 += k;
	m1._42 += k;
	m1._43 += k;
	m1._44 += k;
}

FORCEINLINE void operator-=(mat4& m1, f32 const k) {
	m1._11 -= k;
	m1._12 -= k;
	m1._13 -= k;
	m1._14 -= k;

	m1._21 -= k;
	m1._22 -= k;
	m1._23 -= k;
	m1._24 -= k;

	m1._31 -= k;
	m1._32 -= k;
	m1._33 -= k;
	m1._34 -= k;

	m1._41 -= k;
	m1._42 -= k;
	m1._43 -= k;
	m1._44 -= k;
}

FORCEINLINE void operator*=(mat4& m1, f32 const k) {
	m1._11 *= k;
	m1._12 *= k;
	m1._13 *= k;
	m1._14 *= k;

	m1._21 *= k;
	m1._22 *= k;
	m1._23 *= k;
	m1._24 *= k;

	m1._31 *= k;
	m1._32 *= k;
	m1._33 *= k;
	m1._34 *= k;

	m1._41 *= k;
	m1._42 *= k;
	m1._43 *= k;
	m1._44 *= k;
}

FORCEINLINE void operator/=(mat4& m1, f32 const k) {
	m1._11 /= k;
	m1._12 /= k;
	m1._13 /= k;
	m1._14 /= k;

	m1._21 /= k;
	m1._22 /= k;
	m1._23 /= k;
	m1._24 /= k;

	m1._31 /= k;
	m1._32 /= k;
	m1._33 /= k;
	m1._34 /= k;

	m1._41 /= k;
	m1._42 /= k;
	m1._43 /= k;
	m1._44 /= k;
}

//-----------------------------------------------------------------------------

FORCEINLINE void operator+=(mat4& m1, mat4 const& m2) {
	m1._11 += m2._11;
	m1._12 += m2._12;
	m1._13 += m2._13;
	m1._14 += m2._14;

	m1._21 += m2._21;
	m1._22 += m2._22;
	m1._23 += m2._23;
	m1._24 += m2._24;

	m1._31 += m2._31;
	m1._32 += m2._32;
	m1._33 += m2._33;
	m1._34 += m2._34;

	m1._41 += m2._41;
	m1._42 += m2._42;
	m1._43 += m2._43;
	m1._44 += m2._44;
}

FORCEINLINE void operator-=(mat4& m1, mat4 const& m2) {
	m1._11 -= m2._11;
	m1._12 -= m2._12;
	m1._13 -= m2._13;
	m1._14 -= m2._14;

	m1._21 -= m2._21;
	m1._22 -= m2._22;
	m1._23 -= m2._23;
	m1._24 -= m2._24;

	m1._31 -= m2._31;
	m1._32 -= m2._32;
	m1._33 -= m2._33;
	m1._34 -= m2._34;

	m1._41 -= m2._41;
	m1._42 -= m2._42;
	m1._43 -= m2._43;
	m1._44 -= m2._44;
}

//-----------------------------------------------------------------------------

FORCEINLINE mat4 operator+(mat4 const& m1, f32 const k) {
	return mat4{
		m1._11 + k,
		m1._12 + k,
		m1._13 + k,
		m1._14 + k,

		m1._21 + k,
		m1._22 + k,
		m1._23 + k,
		m1._24 + k,

		m1._31 + k,
		m1._32 + k,
		m1._33 + k,
		m1._34 + k,

		m1._41 + k,
		m1._42 + k,
		m1._43 + k,
		m1._44 + k
	};
}

FORCEINLINE mat4 operator-(mat4 const& m1, f32 const k) {
	return mat4{
		m1._11 - k,
		m1._12 - k,
		m1._13 - k,
		m1._14 - k,

		m1._21 - k,
		m1._22 - k,
		m1._23 - k,
		m1._24 - k,

		m1._31 - k,
		m1._32 - k,
		m1._33 - k,
		m1._34 - k,

		m1._41 - k,
		m1._42 - k,
		m1._43 - k,
		m1._44 - k
	};
}

FORCEINLINE mat4 operator*(mat4 const& m1, f32 const k) {
	return mat4{
		m1._11 * k,
		m1._12 * k,
		m1._13 * k,
		m1._14 * k,

		m1._21 * k,
		m1._22 * k,
		m1._23 * k,
		m1._24 * k,

		m1._31 * k,
		m1._32 * k,
		m1._33 * k,
		m1._34 * k,

		m1._41 * k,
		m1._42 * k,
		m1._43 * k,
		m1._44 * k
	};
}

FORCEINLINE mat4 operator/(mat4 const& m1, f32 const k) {
	return mat4{
		m1._11 / k,
		m1._12 / k,
		m1._13 / k,
		m1._14 / k,

		m1._21 / k,
		m1._22 / k,
		m1._23 / k,
		m1._24 / k,

		m1._31 / k,
		m1._32 / k,
		m1._33 / k,
		m1._34 / k,

		m1._41 / k,
		m1._42 / k,
		m1._43 / k,
		m1._44 / k
	};
}

//-----------------------------------------------------------------------------

FORCEINLINE mat4 operator+(f32 const k, mat4 const& m1) {
	return m1 + k;
}

FORCEINLINE mat4 operator-(f32 const k, mat4 const& m1) {
	return m1 - k;
}

FORCEINLINE mat4 operator*(f32 const k, mat4 const& m1) {
	return m1 * k;
}

FORCEINLINE mat4 operator/(f32 const k, mat4 const& m1) {
	return m1 / k;
}

//-----------------------------------------------------------------------------

FORCEINLINE mat4 operator+(mat4 const& m1, mat4 const& m2) {
	return mat4{
		m1._11 + m2._11,
		m1._12 + m2._12,
		m1._13 + m2._13,
		m1._14 + m2._14,

		m1._21 + m2._21,
		m1._22 + m2._22,
		m1._23 + m2._23,
		m1._24 + m2._24,

		m1._31 + m2._31,
		m1._32 + m2._32,
		m1._33 + m2._33,
		m1._34 + m2._34,

		m1._41 + m2._41,
		m1._42 + m2._42,
		m1._43 + m2._43,
		m1._44 + m2._44
	};
}

FORCEINLINE mat4 operator-(mat4 const& m1, mat4 const& m2) {
	return mat4{
		m1._11 - m2._11,
		m1._12 - m2._12,
		m1._13 - m2._13,
		m1._14 - m2._14,

		m1._21 - m2._21,
		m1._22 - m2._22,
		m1._23 - m2._23,
		m1._24 - m2._24,

		m1._31 - m2._31,
		m1._32 - m2._32,
		m1._33 - m2._33,
		m1._34 - m2._34,

		m1._41 - m2._41,
		m1._42 - m2._42,
		m1._43 - m2._43,
		m1._44 - m2._44
	};
}

FORCEINLINE mat4 operator*(mat4 const& m1, mat4 const& m2) {
	return mat4{
		(m1._11 * m2._11) + (m1._12 * m2._21) + (m1._13 * m2._31) + (m1._14 * m2._41),
		(m1._11 * m2._12) + (m1._12 * m2._22) + (m1._13 * m2._32) + (m1._14 * m2._42),
		(m1._11 * m2._13) + (m1._12 * m2._23) + (m1._13 * m2._33) + (m1._14 * m2._43),
		(m1._11 * m2._14) + (m1._12 * m2._24) + (m1._13 * m2._34) + (m1._14 * m2._44),

		(m1._21 * m2._11) + (m1._22 * m2._21) + (m1._23 * m2._31) + (m1._24 * m2._41),
		(m1._21 * m2._12) + (m1._22 * m2._22) + (m1._23 * m2._32) + (m1._24 * m2._42),
		(m1._21 * m2._13) + (m1._22 * m2._23) + (m1._23 * m2._33) + (m1._24 * m2._43),
		(m1._21 * m2._14) + (m1._22 * m2._24) + (m1._23 * m2._34) + (m1._24 * m2._44),

		(m1._31 * m2._11) + (m1._32 * m2._21) + (m1._33 * m2._31) + (m1._34 * m2._41),
		(m1._31 * m2._12) + (m1._32 * m2._22) + (m1._33 * m2._32) + (m1._34 * m2._42),
		(m1._31 * m2._13) + (m1._32 * m2._23) + (m1._33 * m2._33) + (m1._34 * m2._43),
		(m1._31 * m2._14) + (m1._32 * m2._24) + (m1._33 * m2._34) + (m1._34 * m2._44),

		(m1._41 * m2._11) + (m1._42 * m2._21) + (m1._43 * m2._31) + (m1._44 * m2._41),
		(m1._41 * m2._12) + (m1._42 * m2._22) + (m1._43 * m2._32) + (m1._44 * m2._42),
		(m1._41 * m2._13) + (m1._42 * m2._23) + (m1._43 * m2._33) + (m1._44 * m2._43),
		(m1._41 * m2._14) + (m1._42 * m2._24) + (m1._43 * m2._34) + (m1._44 * m2._44)
	};
}

//=============================================================================
// mat4 functions.
//=============================================================================

namespace Mat4 {

// Matrix transpose.
CONSTEXPR mat4 Tranpose(mat4 const& m1) {
	return mat4{
		m1._11, m1._21, m1._31, m1._41,
		m1._12, m1._22, m1._32, m1._42,
		m1._13, m1._23, m1._33, m1._43,
		m1._14, m1._24, m1._34, m1._44
	};
}

// Matrix determinant.
f32 Determinant(mat4 const& m1);

// Matrix inverse.
mat4 Inverse(mat4 const& m1, mat4 const& m2);

// Left-handed perspective projection matrix with FOV given in horizontal degrees.
mat4 PerspectiveFOV(f32 fov, vec2 view, f32 zNear, f32 zFar);

// Returns a rotation transform matrix for an angle in radians around a given axis.
mat4 RotationAxis(vec3 axis, f32 angle);

// Returns a rotation transform matrix for an angle in radians around the x-axis.
mat4 RotationX(f32 angle);

// Returns a rotation transform matrix for an angle in radians around the y-axis.
mat4 RotationY(f32 angle);

// Returns a rotation transform matrix for an angle in radians around the z-axis.
mat4 RotationZ(f32 angle);

// Returns a translation transformation matrix for the given offset.
mat4 Translation(vec3 offset);

// Returns a rotation transformation matrix for the givne yaw pitch and roll values in radians.
mat4 YawPitchRoll(f32 yaw, f32 pitch, f32 roll);

};