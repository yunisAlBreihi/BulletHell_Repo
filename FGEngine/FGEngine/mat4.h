#pragma once
#include "float3.h"

struct mat4
{
	float c[16];

	const mat4 operator*(const mat4& rhs) const
	{
		mat4 ret;
		for (int i = 0; i < 16; i++)
		{
			ret.c[i] = c[i] * rhs.c[i];
		}
		return ret;
	}
};

#undef far
#undef near
class mat4Util
{
public:
	static inline mat4 ortho(float left, float right, float bottom, float top, float near, float far)
	{
		float tx = (left + right) / (right -left);
		float ty = (top + bottom) / (top - bottom);
		float tz = (far + near) / (far - near);

		mat4 ortho;
		ortho.c[0] = 2.0f / (right - left);
		ortho.c[1] = 0;
		ortho.c[2] = 0;
		ortho.c[3] = 0;
		ortho.c[4] = 0;
		ortho.c[5] = 2.0f / (top - bottom);
		ortho.c[6] = 0;
		ortho.c[7] = 0;
		ortho.c[8] = 0;
		ortho.c[9] = -2.0f / (far - near);
		ortho.c[10] = 0;
		ortho.c[11] = 0;
		ortho.c[12] = tx;
		ortho.c[13] = ty;
		ortho.c[14] = tz;
		ortho.c[15] = 1;
		return ortho;
	}

	static inline void lookAt(mat4& m, const float3& from, const float3& to, const float3& worldUp)
	{
		float3 forward = float3Util::normalize(from - to);
		float3 right = float3Util::crossProduct(worldUp, forward);
		float3 up = float3Util::crossProduct(forward, right);

		m.c[0] = right.x;
		m.c[1] = right.y;
		m.c[2] = right.z;
		m.c[3] = 0;
		m.c[4] = up.x;
		m.c[5] = up.y;
		m.c[6] = up.z;
		m.c[7] = 0;
		m.c[8] = forward.x;
		m.c[9] = forward.y;
		m.c[10] = forward.z;
		m.c[11] = 0;
		m.c[12] = from.x;
		m.c[13] = from.y;
		m.c[14] = from.z;
		m.c[15] = 1;
	}
};
