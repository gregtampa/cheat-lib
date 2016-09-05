#pragma once
#include "Types.hpp"
#include <math.h>

//=============================================================================
// int2 operators.
//=============================================================================

FORCEINLINE void operator+=(int2& v1, i32 const k) {
	v1.x += k;
	v1.y += k;
}

FORCEINLINE void operator-=(int2& v1, i32 const k) {
	v1.x -= k;
	v1.y -= k;
}

FORCEINLINE void operator*=(int2& v1, i32 const k) {
	v1.x *= k;
	v1.y *= k;
}

FORCEINLINE void operator/=(int2& v1, i32 const k) {
	v1.x /= k;
	v1.y /= k;
}

//-----------------------------------------------------------------------------

FORCEINLINE void operator+=(int2& v1, int2 const v2) {
	v1.x += v2.x;
	v1.y += v2.y;
}

FORCEINLINE void operator-=(int2& v1, int2 const v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
}

FORCEINLINE void operator*=(int2& v1, int2 const v2) {
	v1.x *= v2.x;
	v1.y *= v2.y;
}

FORCEINLINE void operator/=(int2& v1, int2 const v2) {
	v1.x /= v2.x;
	v1.y /= v2.y;
}

//-----------------------------------------------------------------------------

CONSTEXPR int2 operator+(int2 const v1, i32 const k) {
	return int2{
		v1.x + k,
		v1.y + k
	};
}

CONSTEXPR int2 operator-(int2 const v1, i32 const k) {
	return int2{
		v1.x - k,
		v1.y - k
	};
}

CONSTEXPR int2 operator*(int2 const v1, i32 const k) {
	return int2{
		v1.x * k,
		v1.y * k
	};
}

CONSTEXPR int2 operator/(int2 const v1, i32 const k) {
	return int2{
		v1.x / k,
		v1.y / k
	};
}

//-----------------------------------------------------------------------------

CONSTEXPR int2 operator+(i32 const k, int2 const v1) {
	return v1 * k;
}

CONSTEXPR int2 operator-(i32 const k, int2 const v1) {
	return v1 * k;
}

CONSTEXPR int2 operator*(i32 const k, int2 const v1) {
	return v1 * k;
}

CONSTEXPR int2 operator/(i32 const k, int2 const v1) {
	return v1 * k;
}

//-----------------------------------------------------------------------------

CONSTEXPR b32 operator==(int2 const v1, int2 const v2) {
	return
		v1.x == v2.x &&
		v1.y == v2.y;
}

CONSTEXPR int2 operator+(int2 const v1, int2 const v2) {
	return int2{
		v1.x + v2.x,
		v1.y + v2.y
	};
}

CONSTEXPR int2 operator-(int2 const v1, int2 const v2) {
	return int2{
		v1.x - v2.x,
		v1.y - v2.y
	};
}

CONSTEXPR int2 operator*(int2 const v1, int2 const v2) {
	return int2{
		v1.x * v2.x,
		v1.y * v2.y
	};
}

CONSTEXPR int2 operator/(int2 const v1, int2 const v2) {
	return int2{
		v1.x / v2.x,
		v1.y / v2.y
	};
}

//=============================================================================
// int3 operators.
//=============================================================================

FORCEINLINE void operator+=(int3& v1, i32 const k) {
	v1.x += k;
	v1.y += k;
	v1.z += k;
}

FORCEINLINE void operator-=(int3& v1, i32 const k) {
	v1.x -= k;
	v1.y -= k;
	v1.z -= k;
}

FORCEINLINE void operator*=(int3& v1, i32 const k) {
	v1.x *= k;
	v1.y *= k;
	v1.z *= k;
}

FORCEINLINE void operator/=(int3& v1, i32 const k) {
	v1.x /= k;
	v1.y /= k;
	v1.z /= k;
}

//-----------------------------------------------------------------------------

FORCEINLINE void operator+=(int3& v1, int3 const v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
}

FORCEINLINE void operator-=(int3& v1, int3 const v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
}

FORCEINLINE void operator*=(int3& v1, int3 const v2) {
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
}

FORCEINLINE void operator/=(int3& v1, int3 const v2) {
	v1.x /= v2.x;
	v1.y /= v2.y;
	v1.z /= v2.z;
}

//-----------------------------------------------------------------------------

CONSTEXPR int3 operator+(int3 const v1, i32 const k) {
	return int3{
		v1.x + k,
		v1.y + k,
		v1.z + k
	};
}

CONSTEXPR int3 operator-(int3 const v1, i32 const k) {
	return int3{
		v1.x - k,
		v1.y - k,
		v1.z - k
	};
}

CONSTEXPR int3 operator*(int3 const v1, i32 const k) {
	return int3{
		v1.x * k,
		v1.y * k,
		v1.z * k
	};
}

CONSTEXPR int3 operator/(int3 const v1, i32 const k) {
	return int3{
		v1.x / k,
		v1.y / k,
		v1.z / k
	};
}

//-----------------------------------------------------------------------------

CONSTEXPR int3 operator+(i32 const k, int3 const v1) {
	return v1 * k;
}

CONSTEXPR int3 operator-(i32 const k, int3 const v1) {
	return v1 * k;
}

CONSTEXPR int3 operator*(i32 const k, int3 const v1) {
	return v1 * k;
}

CONSTEXPR int3 operator/(i32 const k, int3 const v1) {
	return v1 * k;
}

//-----------------------------------------------------------------------------

CONSTEXPR b32 operator==(int3 const v1, int3 const v2) {
	return
		v1.x == v2.x &&
		v1.y == v2.y &&
		v1.z == v2.z;
}

CONSTEXPR int3 operator+(int3 const v1, int3 const v2) {
	return int3{
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	};
}

CONSTEXPR int3 operator-(int3 const v1, int3 const v2) {
	return int3{
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	};
}

CONSTEXPR int3 operator*(int3 const v1, int3 const v2) {
	return int3{
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z
	};
}

CONSTEXPR int3 operator/(int3 const v1, int3 const v2) {
	return int3{
		v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z
	};
}

//=============================================================================
// int4 operators.
//=============================================================================

FORCEINLINE void operator+=(int4& v1, i32 const k) {
	v1.x += k;
	v1.y += k;
	v1.z += k;
	v1.w += k;
}

FORCEINLINE void operator-=(int4& v1, i32 const k) {
	v1.x -= k;
	v1.y -= k;
	v1.z -= k;
	v1.w -= k;
}

FORCEINLINE void operator*=(int4& v1, i32 const k) {
	v1.x *= k;
	v1.y *= k;
	v1.z *= k;
	v1.w *= k;
}

FORCEINLINE void operator/=(int4& v1, i32 const k) {
	v1.x /= k;
	v1.y /= k;
	v1.z /= k;
	v1.w /= k;
}

//-----------------------------------------------------------------------------

FORCEINLINE void operator+=(int4& v1, int4 const v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	v1.w += v2.w;
}

FORCEINLINE void operator-=(int4& v1, int4 const v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	v1.w -= v2.w;
}

FORCEINLINE void operator*=(int4& v1, int4 const v2) {
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	v1.w *= v2.w;
}

FORCEINLINE void operator/=(int4& v1, int4 const v2) {
	v1.x /= v2.x;
	v1.y /= v2.y;
	v1.z /= v2.z;
	v1.w /= v2.w;
}

//-----------------------------------------------------------------------------

CONSTEXPR int4 operator+(int4 const v1, i32 const k) {
	return int4{
		v1.x + k,
		v1.y + k,
		v1.z + k,
		v1.w + k
	};
}

CONSTEXPR int4 operator-(int4 const v1, i32 const k) {
	return int4{
		v1.x - k,
		v1.y - k,
		v1.z - k,
		v1.w - k
	};
}

CONSTEXPR int4 operator*(int4 const v1, i32 const k) {
	return int4{
		v1.x * k,
		v1.y * k,
		v1.z * k,
		v1.w * k
	};
}

CONSTEXPR int4 operator/(int4 const v1, i32 const k) {
	return int4{
		v1.x / k,
		v1.y / k,
		v1.z / k,
		v1.w / k
	};
}

//-----------------------------------------------------------------------------

CONSTEXPR int4 operator+(i32 const k, int4 const v1) {
	return v1 * k;
}

CONSTEXPR int4 operator-(i32 const k, int4 const v1) {
	return v1 * k;
}

CONSTEXPR int4 operator*(i32 const k, int4 const v1) {
	return v1 * k;
}

CONSTEXPR int4 operator/(i32 const k, int4 const v1) {
	return v1 * k;
}

//-----------------------------------------------------------------------------

CONSTEXPR b32 operator==(int4 const v1, int4 const v2) {
	return
		v1.x == v2.x &&
		v1.y == v2.y &&
		v1.z == v2.z;
}

CONSTEXPR int4 operator+(int4 const v1, int4 const v2) {
	return int4{
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z,
		v1.w + v2.w
	};
}

CONSTEXPR int4 operator-(int4 const v1, int4 const v2) {
	return int4{
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z,
		v1.w - v2.w
	};
}

CONSTEXPR int4 operator*(int4 const v1, int4 const v2) {
	return int4{
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z,
		v1.w * v2.w
	};
}

FORCEINLINE int4 operator/(int4 const v1, int4 const v2) {
	return int4{
		v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z,
		v1.w / v2.w
	};
}

//=============================================================================
// vec2 operators.
//=============================================================================

FORCEINLINE void operator+=(vec2& v1, f32 const k) {
	v1.x += k;
	v1.y += k;
}

FORCEINLINE void operator-=(vec2& v1, f32 const k) {
	v1.x -= k;
	v1.y -= k;
}

FORCEINLINE void operator*=(vec2& v1, f32 const k) {
	v1.x *= k;
	v1.y *= k;
}

FORCEINLINE void operator/=(vec2& v1, f32 const k) {
	v1.x /= k;
	v1.y /= k;
}

//-----------------------------------------------------------------------------

FORCEINLINE void operator+=(vec2& v1, vec2 const v2) {
	v1.x += v2.x;
	v1.y += v2.y;
}

FORCEINLINE void operator-=(vec2& v1, vec2 const v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
}

FORCEINLINE void operator*=(vec2& v1, vec2 const v2) {
	v1.x *= v2.x;
	v1.y *= v2.y;
}

FORCEINLINE void operator/=(vec2& v1, vec2 const v2) {
	v1.x /= v2.x;
	v1.y /= v2.y;
}

//-----------------------------------------------------------------------------

CONSTEXPR vec2 operator+(vec2 const v1, f32 const k) {
	return vec2{
		v1.x + k,
		v1.y + k
	};
}

CONSTEXPR vec2 operator-(vec2 const v1, f32 const k) {
	return vec2{
		v1.x - k,
		v1.y - k
	};
}

CONSTEXPR vec2 operator*(vec2 const v1, f32 const k) {
	return vec2{
		v1.x * k,
		v1.y * k
	};
}

CONSTEXPR vec2 operator/(vec2 const v1, f32 const k) {
	return vec2{
		v1.x / k,
		v1.y / k
	};
}

//-----------------------------------------------------------------------------

CONSTEXPR vec2 operator+(f32 const k, vec2 const v1) {
	return v1 * k;
}

CONSTEXPR vec2 operator-(f32 const k, vec2 const v1) {
	return v1 * k;
}

CONSTEXPR vec2 operator*(f32 const k, vec2 const v1) {
	return v1 * k;
}

CONSTEXPR vec2 operator/(f32 const k, vec2 const v1) {
	return v1 * k;
}

//-----------------------------------------------------------------------------

CONSTEXPR b32 operator==(vec2 const v1, vec2 const v2) {
	return
		v1.x == v2.x &&
		v1.y == v2.y;
}

CONSTEXPR vec2 operator+(vec2 const v1, vec2 const v2) {
	return vec2{
		v1.x + v2.x,
		v1.y + v2.y
	};
}

CONSTEXPR vec2 operator-(vec2 const v1, vec2 const v2) {
	return vec2{
		v1.x - v2.x,
		v1.y - v2.y
	};
}

CONSTEXPR vec2 operator*(vec2 const v1, vec2 const v2) {
	return vec2{
		v1.x * v2.x,
		v1.y * v2.y
	};
}

CONSTEXPR vec2 operator/(vec2 const v1, vec2 const v2) {
	return vec2{
		v1.x / v2.x,
		v1.y / v2.y
	};
}

//=============================================================================
// vec3 operators.
//=============================================================================

FORCEINLINE void operator+=(vec3& v1, f32 const k) {
	v1.x += k;
	v1.y += k;
	v1.z += k;
}

FORCEINLINE void operator-=(vec3& v1, f32 const k) {
	v1.x -= k;
	v1.y -= k;
	v1.z -= k;
}

FORCEINLINE void operator*=(vec3& v1, f32 const k) {
	v1.x *= k;
	v1.y *= k;
	v1.z *= k;
}

FORCEINLINE void operator/=(vec3& v1, f32 const k) {
	v1.x /= k;
	v1.y /= k;
	v1.z /= k;
}

//-----------------------------------------------------------------------------

FORCEINLINE void operator+=(vec3& v1, vec3 const v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
}

FORCEINLINE void operator-=(vec3& v1, vec3 const v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
}

FORCEINLINE void operator*=(vec3& v1, vec3 const v2) {
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
}

FORCEINLINE void operator/=(vec3& v1, vec3 const v2) {
	v1.x /= v2.x;
	v1.y /= v2.y;
	v1.z /= v2.z;
}

//-----------------------------------------------------------------------------

CONSTEXPR vec3 operator+(vec3 const v1, f32 const k) {
	return vec3{
		v1.x + k,
		v1.y + k,
		v1.z + k
	};
}

CONSTEXPR vec3 operator-(vec3 const v1, f32 const k) {
	return vec3{
		v1.x - k,
		v1.y - k,
		v1.z - k
	};
}

CONSTEXPR vec3 operator*(vec3 const v1, f32 const k) {
	return vec3{
		v1.x * k,
		v1.y * k,
		v1.z * k
	};
}

CONSTEXPR vec3 operator/(vec3 const v1, f32 const k) {
	return vec3{
		v1.x / k,
		v1.y / k,
		v1.z / k
	};
}

//-----------------------------------------------------------------------------

CONSTEXPR vec3 operator+(f32 const k, vec3 const v1) {
	return v1 * k;
}

CONSTEXPR vec3 operator-(f32 const k, vec3 const v1) {
	return v1 * k;
}

CONSTEXPR vec3 operator*(f32 const k, vec3 const v1) {
	return v1 * k;
}

CONSTEXPR vec3 operator/(f32 const k, vec3 const v1) {
	return v1 * k;
}

//-----------------------------------------------------------------------------

CONSTEXPR b32 operator==(vec3 const v1, vec3 const v2) {
	return
		v1.x == v2.x &&
		v1.y == v2.y &&
		v1.z == v2.z;
}

CONSTEXPR vec3 operator+(vec3 const v1, vec3 const v2) {
	return vec3{
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z
	};
}

CONSTEXPR vec3 operator-(vec3 const v1, vec3 const v2) {
	return vec3{
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	};
}

CONSTEXPR vec3 operator*(vec3 const v1, vec3 const v2) {
	return vec3{
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z
	};
}

CONSTEXPR vec3 operator/(vec3 const v1, vec3 const v2) {
	return vec3{
		v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z
	};
}

//=============================================================================
// vec4 operators.
//=============================================================================

FORCEINLINE void operator+=(vec4& v1, f32 const k) {
	v1.x += k;
	v1.y += k;
	v1.z += k;
	v1.w += k;
}

FORCEINLINE void operator-=(vec4& v1, f32 const k) {
	v1.x -= k;
	v1.y -= k;
	v1.z -= k;
	v1.w -= k;
}

FORCEINLINE void operator*=(vec4& v1, f32 const k) {
	v1.x *= k;
	v1.y *= k;
	v1.z *= k;
	v1.w *= k;
}

FORCEINLINE void operator/=(vec4& v1, f32 const k) {
	v1.x /= k;
	v1.y /= k;
	v1.z /= k;
	v1.w /= k;
}

//-----------------------------------------------------------------------------

FORCEINLINE void operator+=(vec4& v1, vec4 const v2) {
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	v1.w += v2.w;
}

FORCEINLINE void operator-=(vec4& v1, vec4 const v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	v1.w -= v2.w;
}

FORCEINLINE void operator*=(vec4& v1, vec4 const v2) {
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	v1.w *= v2.w;
}

FORCEINLINE void operator/=(vec4& v1, vec4 const v2) {
	v1.x /= v2.x;
	v1.y /= v2.y;
	v1.z /= v2.z;
	v1.w /= v2.w;
}

//-----------------------------------------------------------------------------

CONSTEXPR vec4 operator+(vec4 const v1, f32 const k) {
	return vec4{
		v1.x + k,
		v1.y + k,
		v1.z + k,
		v1.w + k
	};
}

CONSTEXPR vec4 operator-(vec4 const v1, f32 const k) {
	return vec4{
		v1.x - k,
		v1.y - k,
		v1.z - k,
		v1.w - k
	};
}

CONSTEXPR vec4 operator*(vec4 const v1, f32 const k) {
	return vec4{
		v1.x * k,
		v1.y * k,
		v1.z * k,
		v1.w * k
	};
}

CONSTEXPR vec4 operator/(vec4 const v1, f32 const k) {
	return vec4{
		v1.x / k,
		v1.y / k,
		v1.z / k,
		v1.w / k
	};
}

//-----------------------------------------------------------------------------

CONSTEXPR vec4 operator+(f32 const k, vec4 const v1) {
	return v1 * k;
}

CONSTEXPR vec4 operator-(f32 const k, vec4 const v1) {
	return v1 * k;
}

CONSTEXPR vec4 operator*(f32 const k, vec4 const v1) {
	return v1 * k;
}

CONSTEXPR vec4 operator/(f32 const k, vec4 const v1) {
	return v1 * k;
}

//-----------------------------------------------------------------------------

CONSTEXPR b32 operator==(vec4 const v1, vec4 const v2) {
	return
		v1.x == v2.x &&
		v1.y == v2.y &&
		v1.z == v2.z &&
		v1.w == v2.w;
}

CONSTEXPR vec4 operator+(vec4 const v1, vec4 const v2) {
	return vec4{
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z,
		v1.w + v2.w
	};
}

CONSTEXPR vec4 operator-(vec4 const v1, vec4 const v2) {
	return vec4{
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z,
		v1.w - v2.w
	};
}

CONSTEXPR vec4 operator*(vec4 const v1, vec4 const v2) {
	return vec4{
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z,
		v1.w * v2.w
	};
}

CONSTEXPR vec4 operator/(vec4 const v1, vec4 const v2) {
	return vec4{
		v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z,
		v1.w / v2.w
	};
}

//=============================================================================
// vec2 functions.
//=============================================================================

namespace Vec2 {

// Vector dot product.
CONSTEXPR f32 Dot(vec2 const v1, vec2 const v2) {
	return
		v1.x * v2.x +
		v1.y * v2.y;
}

// Vector length.
FORCEINLINE f32 Length(vec2 const v1) {
	return sqrtf(
		v1.x * v1.x +
		v1.y * v1.y
	);
}

// Vector normalization.
FORCEINLINE vec2 Normalize(vec2 const v1) {
	f32 const norm = 1.0f / sqrtf(v1.x * v1.x + v1.y * v1.y);

	if (norm == 0.0f) {
		return vec2{ 0.0f, 0.0f };
	}

	return vec2{
		v1.x * norm,
		v1.y * norm
	};
}

// Rotates a point around an angle in radians.
FORCEINLINE vec2 Rotate(vec2 const v1, f32 angle) {
	f32 ca = cosf(angle);
	f32 sa = sinf(angle);

	return vec2{ 
		v1.x * ca - v1.y * sa, 
		v1.y * ca + v1.x * sa 
	};
}

}

//=============================================================================
// vec3 functions.
//=============================================================================

namespace Vec3 {

// Vector cross product. r = v1 x v2.
CONSTEXPR vec3 Cross(vec3 const v1, vec3 const v2) {
	return vec3{
		(v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x)
	};
}

// Vector dot product.
CONSTEXPR f32 Dot(vec3 const v1, vec3 const v2) {
	return
		v1.x * v2.x +
		v1.y * v2.y +
		v1.z * v2.z;
}

// Vector length.
FORCEINLINE f32 Length(vec3 const v1) {
	return sqrtf(
		v1.x * v1.x +
		v1.y * v1.y +
		v1.z * v1.z
	);
}

// Vector normalization.
FORCEINLINE vec3 Normalize(vec3 const v1) {
	f32 const norm = 1.0f / sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);

	if (norm == 0.0f) {
		return vec3{ 0.0f, 0.0f, 0.0f };
	}

	return vec3{
		v1.x * norm,
		v1.y * norm,
		v1.z * norm
	};
}

// Transforms vector (x, y, z, 1) by a given matrix.
CONSTEXPR vec4 Transform(vec3 const v1, mat4 const& m1) {
	return vec4{
		m1._11 * v1.x + m1._21 * v1.y + m1._31 * v1.z + m1._41,
		m1._12 * v1.x + m1._22 * v1.y + m1._32 * v1.z + m1._42,
		m1._13 * v1.x + m1._23 * v1.y + m1._33 * v1.z + m1._43,
		m1._14 * v1.x + m1._24 * v1.y + m1._34 * v1.z + m1._44
	};
}

// Transforms a 3D vector by a given matrix, projecting the result back into w = 1.
FORCEINLINE vec3 TransformCoord(vec3 const v1, mat4 const& m1) {
	f32 const norm = m1._14 * v1.x + m1._24 * v1.y + m1._34 *v1.z + m1._44;

	return vec3{
		(m1._11 * v1.x + m1._21 * v1.y + m1._31 * v1.z + m1._41) / norm,
		(m1._12 * v1.x + m1._22 * v1.y + m1._32 * v1.z + m1._42) / norm,
		(m1._13 * v1.x + m1._23 * v1.y + m1._33 * v1.z + m1._43) / norm
	};
}

// Transforms the 3D vector normal by the given matrix.
CONSTEXPR vec3 TransformNormal(vec3 const v1, mat4 const& m1) {
	return vec3{
		m1._11 * v1.x + m1._21 * v1.y + m1._31 * v1.z,
		m1._12 * v1.x + m1._22 * v1.y + m1._32 * v1.z,
		m1._13 * v1.x + m1._23 * v1.y + m1._33 * v1.z
	};
}

}

//=============================================================================
// vec4 functions.
//=============================================================================

namespace Vec4 {

// Vector cross product. r = v1 x v2.
CONSTEXPR vec4 Cross(vec4 const v1, vec4 const v2) {
	return vec4{
		(v1.y * v2.z) - (v1.z * v2.y),
		(v1.z * v2.x) - (v1.x * v2.z),
		(v1.x * v2.y) - (v1.y * v2.x),
		1.0f
	};
}

// Vector dot product.
CONSTEXPR f32 Dot(vec4 const v1, vec4 const v2) {
	return
		v1.x * v2.x +
		v1.y * v2.y +
		v1.z * v2.z +
		v1.w * v2.w;
}

// Vector length.
FORCEINLINE f32 Length(vec4 const v1) {
	return sqrtf(
		v1.x * v1.x +
		v1.y * v1.y +
		v1.z * v1.z +
		v1.w * v1.w
	);
}

// Vector normalization.
FORCEINLINE vec4 Normalize(vec4 const v1) {
	f32 const norm = 1.0f / sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z + v1.w * v1.w);

	if (norm == 0.0f) {
		return vec4{ 0.0f, 0.0f, 0.0f, 0.0f };
	}

	return vec4{
		v1.x * norm,
		v1.y * norm,
		v1.z * norm,
		v1.w * norm
	};
}

}
