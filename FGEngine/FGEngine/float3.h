#pragma once
#include <cmath>


struct float3
{
	inline float3(float a = 0.0f)
		:x(a), y(a), z(a) { }
	inline float3(float x, float y, float z)
		: x(x), y(y), z(z) { }

	inline ~float3() = default;

	union
	{
		float x;
		float r;
	};

	union
	{
		float y;
		float g;
	};

	union
	{
		float z;
		float b;
	};

	inline float& operator[](const size_t& i)
	{
		return *(((float*)this) + i);
	}

	inline const float& operator[](const size_t& i) const
	{
		return *(((float*)this) + i);
	}

	inline float3& operator=(const float3& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return (*this);
	}

	inline float3& operator+=(const float3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return (*this);
	}

	inline float3 operator+(const float3& rhs) const
	{
		return float3(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	inline float3 operator-(const float3& rhs) const
	{
		return float3(x - rhs.x, y - rhs.y, z - rhs.z);
	}

	inline float3& operator-=(const float3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return (*this);
	}

	inline float3& operator *=(const float& rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;
		return (*this);
	}

	inline float3 operator*(const float& rhs) const
	{
		return float3(x * rhs, y * rhs, z * rhs);
	}

	inline bool operator==(const float3& rhs) const
	{
		return x == rhs.x && y == rhs.y && x == rhs.z;
	}

	inline bool operator==(const float& rhs) const
	{
		return x == rhs && y == rhs && z == rhs;
	}
}; 

class float3Util
{
public:
	static float3 normalize(const float3& v)
	{
		float length(v.x * v.x + v.y * v.y + v.z * v.z);

		if (std::fabs(length) == 1.0f)
			return v;

		length = 1.0f / std::sqrt(length);
		return float3(v.x * length, v.y * length, v.z * length);
	}

	static float3 crossProduct(const float3& v1, const float3& v2)
	{
		const float NEW_X(v1.y * v2.z - v1.z * v2.y);
		const float NEW_Y(v1.z * v2.x - v1.x * v2.z);
		const float NEW_Z(v1.x * v2.y - v1.y * v2.x);
		return float3(NEW_X, NEW_Y, NEW_Z);
	}

};