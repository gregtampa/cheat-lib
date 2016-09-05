#include "Matrix.hpp"
#include "Vector.hpp"
#include "Math.hpp"
#include <math.h>

f32 Mat4::Determinant(mat4 const& m1) {
	return
		m1._11 * m1._22 * m1._33 * m1._44 +
		m1._11 * m1._23 * m1._34 * m1._42 +
		m1._11 * m1._24 * m1._32 * m1._43 +
		m1._12 * m1._21 * m1._34 * m1._43 +
		m1._12 * m1._23 * m1._31 * m1._44 +
		m1._12 * m1._24 * m1._33 * m1._41 +
		m1._13 * m1._21 * m1._32 * m1._44 +
		m1._13 * m1._22 * m1._34 * m1._41 +
		m1._13 * m1._24 * m1._31 * m1._42 +
		m1._14 * m1._21 * m1._33 * m1._42 +
		m1._14 * m1._22 * m1._31 * m1._43 +
		m1._14 * m1._23 * m1._32 * m1._31 -
		m1._11 * m1._22 * m1._34 * m1._43 -
		m1._11 * m1._23 * m1._32 * m1._44 -
		m1._11 * m1._24 * m1._33 * m1._42 -
		m1._12 * m1._21 * m1._33 * m1._44 -
		m1._12 * m1._23 * m1._34 * m1._41 -
		m1._12 * m1._24 * m1._31 * m1._43 -
		m1._13 * m1._21 * m1._34 * m1._42 -
		m1._13 * m1._22 * m1._31 * m1._44 -
		m1._13 * m1._24 * m1._32 * m1._41 -
		m1._14 * m1._21 * m1._32 * m1._43 -
		m1._14 * m1._22 * m1._33 * m1._41 -
		m1._14 * m1._23 * m1._31 * m1._42;
}

mat4 Mat4::Inverse(mat4 const& m1, mat4 const& m2) {
	f32 s1 = m1._11 * m1._22 - m1._21 * m1._12;
	f32 s2 = m1._11 * m1._23 - m1._21 * m1._13;
	f32 s3 = m1._11 * m1._24 - m1._21 * m1._14;
	f32 s4 = m1._12 * m1._23 - m1._22 * m1._13;
	f32 s5 = m1._12 * m1._24 - m1._22 * m1._14;
	f32 s6 = m1._13 * m1._24 - m1._23 * m1._14;

	f32 c1 = m1._31 * m1._42 - m1._41 * m1._32;
	f32 c2 = m1._31 * m1._43 - m1._41 * m1._33;
	f32 c3 = m1._31 * m1._44 - m1._41 * m1._34;
	f32 c4 = m1._32 * m1._43 - m1._42 * m1._33;
	f32 c5 = m1._32 * m1._44 - m1._42 * m1._34;
	f32 c6 = m1._33 * m1._44 - m1._43 * m1._34;

	f32 k = 1.0f / (s1 * c6 - s2 * c5 + s3 * c4 + s4 * c3 - s5 * c2 + s6 * c1);

	mat4 m;

	m._11 = (+m1._22 * c6 - m1._23 * c5 + m1._24 * c4) * k;
	m._12 = (-m1._12 * c6 + m1._13 * c5 - m1._14 * c4) * k;
	m._13 = (+m1._42 * s6 - m1._43 * s5 + m1._44 * s4) * k;
	m._14 = (-m1._32 * s6 + m1._33 * s5 - m1._34 * s4) * k;

	m._21 = (-m1._21 * c6 + m1._23 * c3 - m1._24 * c2) * k;
	m._22 = (+m1._11 * c6 - m1._13 * c3 + m1._14 * c2) * k;
	m._23 = (-m1._41 * s6 + m1._43 * s3 - m1._44 * s2) * k;
	m._24 = (+m1._31 * s6 - m1._33 * s3 + m1._34 * s2) * k;

	m._31 = (+m1._21 * c5 - m1._22 * c3 + m1._24 * c1) * k;
	m._32 = (-m1._11 * c5 + m1._12 * c3 - m1._14 * c1) * k;
	m._33 = (+m1._41 * s5 - m1._42 * s3 + m1._44 * s1) * k;
	m._34 = (-m1._31 * s5 + m1._32 * s3 - m1._34 * s1) * k;

	m._41 = (-m1._21 * c4 + m1._22 * c2 - m1._23 * c1) * k;
	m._42 = (+m1._11 * c4 - m1._12 * c2 + m1._13 * c1) * k;
	m._43 = (-m1._41 * s4 + m1._42 * s2 - m1._43 * s1) * k;
	m._44 = (+m1._31 * s4 - m1._32 * s2 + m1._33 * s1) * k;

	return m;
}

mat4 Mat4::PerspectiveFOV(f32 fov, vec2 view, f32 zNear, f32 zFar) {
	f32 const aspect = view.y / view.x;
	f32 const f = (f32)(1.0 / tan(fov * MATH_DEG_TO_RAD / 2.0));
	mat4 m;

	m._11 = f;
	m._12 = 0.0f;
	m._13 = 0.0f;
	m._14 = 0.0f;

	m._21 = 0.0f;
	m._22 = f / aspect;
	m._23 = 0.0f;
	m._24 = 0.0f;

	m._31 = 0.0f;
	m._32 = 0.0f;
	m._33 = zFar / (zFar - zNear);
	m._34 = 1.0f;

	m._41 = 0.0f;
	m._42 = 0.0f;
	m._43 = (zNear * zNear) / (zNear - zFar);
	m._44 = 0.0f;

	return m;
}

mat4 Mat4::RotationAxis(vec3 axis, f32 angle) {
	f32 s = sinf(angle);
	f32 c = cosf(angle);
	f32 cdiff = 1.0f - c;
	vec3 nv = Vec3::Normalize(axis);

	mat4 m;

	m._11 = cdiff * nv.x * nv.x + c;
	m._12 = cdiff * nv.y * nv.x + s * nv.z;
	m._13 = cdiff * nv.z * nv.x - s * nv.y;
	m._14 = 0.0f;

	m._21 = cdiff * nv.x * nv.y - s * nv.z;
	m._22 = cdiff * nv.y * nv.y + c;
	m._23 = cdiff * nv.z * nv.y + s * nv.x;
	m._24 = 0.0f;

	m._31 = cdiff * nv.x * nv.z + s * nv.y;
	m._32 = cdiff * nv.y * nv.z - s * nv.x;
	m._33 = cdiff * nv.z * nv.z + c;
	m._34 = 0.0f;

	m._41 = 0.0f;
	m._42 = 0.0f;
	m._43 = 0.0f;
	m._44 = 1.0f;

	return m;
}

mat4 Mat4::RotationX(f32 angle) {
	f32 c = cosf(angle);
	f32 s = sinf(angle);

	mat4 m;

	m._11 = 1.0f;
	m._12 = 0.0f;
	m._13 = 0.0f;
	m._14 = 0.0f;

	m._21 = 0.0f;
	m._22 = c;
	m._23 = s;
	m._24 = 0.0f;

	m._31 = 0.0f;
	m._32 = -s;
	m._33 = c;
	m._34 = 0.0f;

	m._41 = 0.0f;
	m._42 = 0.0f;
	m._43 = 0.0f;
	m._44 = 1.0f;

	return m;
}

mat4 Mat4::RotationY(f32 angle) {
	f32 c = cosf(angle);
	f32 s = sinf(angle);

	mat4 m;

	m._11 = c;
	m._12 = 0.0f;
	m._13 = -s;
	m._14 = 0.0f;

	m._21 = 0.0f;
	m._22 = 1.0f;
	m._23 = 0.0f;
	m._24 = 0.0f;

	m._31 = s;
	m._32 = 0.0f;
	m._33 = c;
	m._34 = 0.0f;

	m._41 = 0.0f;
	m._42 = 0.0f;
	m._43 = 0.0f;
	m._44 = 1.0f;

	return m;
}

mat4 Mat4::RotationZ(f32 angle) {
	f32 c = cosf(angle);
	f32 s = sinf(angle);

	mat4 m;

	m._11 = c;
	m._12 = s;
	m._13 = 0.0f;
	m._14 = 0.0f;

	m._21 = -s;
	m._22 = c;
	m._23 = 0.0f;
	m._24 = 0.0f;

	m._31 = 0.0f;
	m._32 = 0.0f;
	m._33 = 1.0f;
	m._34 = 0.0f;

	m._41 = 0.0f;
	m._42 = 0.0f;
	m._43 = 0.0f;
	m._44 = 1.0f;

	return m;
}

mat4 Mat4::Translation(vec3 offset) {
	mat4 m;

	m._11 = 1.0f;
	m._12 = 0.0f;
	m._13 = 0.0f;
	m._14 = 0.0f;

	m._21 = 0.0f;
	m._22 = 1.0f;
	m._23 = 0.0f;
	m._24 = 0.0f;

	m._31 = 0.0f;
	m._32 = 0.0f;
	m._33 = 1.0f;
	m._34 = 0.0f;

	m._41 = offset.x;
	m._42 = offset.y;
	m._43 = offset.z;
	m._44 = 1.0f;

	return m;
}

mat4 Mat4::YawPitchRoll(f32 yaw, f32 pitch, f32 roll) {
	f32 sroll = sinf(roll);
	f32 croll = cosf(roll);
	f32 spitch = sinf(pitch);
	f32 cpitch = cosf(pitch);
	f32 syaw = sinf(yaw);
	f32 cyaw = cosf(yaw);

	mat4 m;

	m._11 = sroll * spitch * syaw + croll * cyaw;
	m._12 = sroll * cpitch;
	m._13 = sroll * spitch * cyaw - croll * syaw;
	m._14 = 0.0f;

	m._21 = croll * spitch * syaw - sroll * cyaw;
	m._22 = croll * cpitch;
	m._23 = croll * spitch * cyaw + sroll * syaw;
	m._24 = 0.0f;

	m._31 = cpitch * syaw;
	m._32 = -spitch;
	m._33 = cpitch * cyaw;
	m._34 = 0.0f;

	m._41 = 0.0f;
	m._42 = 0.0f;
	m._43 = 0.0f;
	m._44 = 1.0f;

	return m;
}
