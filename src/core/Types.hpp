#pragma once

//=============================================================================
// Compiler specific declaratives.
//=============================================================================

// Data structure and variable alignment to an x-byte boundary.
#define ALIGN(x) __declspec(align(x))

// Constexpr. Current function support is buggy in VS 2015 (v140) so it's just marked as inline for now.
#define CONSTEXPR __forceinline

// Forces the compiler to inline a function.
#define FORCEINLINE __forceinline

//=============================================================================
// Basic type definitions.
//=============================================================================

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long int i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long int u64;

typedef float f32;
typedef double f64;

typedef i32 b32;
#define false 0
#define true 1

//=============================================================================
// Value limits.
//=============================================================================

#define I8_MAX 127
#define I16_MAX 32767
#define I32_MAX 2147483647
#define I64_MAX 9223372036854775807ll

#define U8_MAX 255
#define U16_MAX 65535
#define U32_MAX 4294967295u
#define U64_MAX 18446744073709551615llu

#define F32_MAX 3.402823466e+38F
#define F64_MAX 1.7976931348623158e+308

//=============================================================================
// Shader (vector, matrix) types.
//=============================================================================

struct int2 {
	i32 x;
	i32 y;
};

struct int3 {
	i32 x;
	i32 y;
	i32 z;
};

struct int4 {
	i32 x;
	i32 y;
	i32 z;
	i32 w;
};

struct vec2 {
	f32 x;
	f32 y;
};

struct vec3 {
	f32 x;
	f32 y;
	f32 z;
};

struct vec4 {
	f32 x;
	f32 y;
	f32 z;
	f32 w;
};

struct mat2 {
	f32 _11, _12;
	f32 _21, _22;
};

struct mat3 {
	f32 _11, _12, _13;
	f32 _21, _22, _23;
	f32 _31, _32, _33;
};

struct mat4 {
	f32 _11, _12, _13, _14;
	f32 _21, _22, _23, _24;
	f32 _31, _32, _33, _34;
	f32 _41, _42, _43, _44;
};
