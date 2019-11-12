#pragma once
//TODO: swizzle, util functions, etc.

struct float4
{
	inline float4(float a = 0.0f)
		:x(a), y(a), z(a), w(a) { }
	inline float4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w) { }

	~float4() = default;

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

	union
	{
		float w;
		float a;
	};

	inline float& operator[](const size_t& i)
	{
		return *(((float*)this) + i);
	}

	inline const float& operator[](const size_t& i) const
	{
		return *(((float*)this) + i);
	}

	inline float4& operator=(const float4& rhs)
	{
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		w = rhs.w;
		return (*this);
	}

	inline float4& operator+=(const float4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return (*this);
	}

	inline float4& operator-=(const float4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return (*this);
	}

	inline bool operator==(const float4& rhs) const
	{
		return x == rhs.x && y == rhs.y && x == rhs.z && w == rhs.w;
	}

	inline bool operator==(const float& rhs) const
	{
		return x == rhs && y == rhs && z == rhs && w == rhs;
	}
};