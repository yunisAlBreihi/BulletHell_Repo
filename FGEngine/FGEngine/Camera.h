#pragma once
#include "Vector2D.h"
#include "float4.h"
#include "float3.h"
#include "mat4.h"
class Input;
class Camera
{
	mat4 view;
	mat4 projection;
	float3 position;

#undef near
#undef far
	float fov, near, far, zoom;

	float3 lookAt;

public:
	Camera(float3 position, float fov, float near, float far);
	void Update(float dt, FG::Vector2D lookAt);
	void SetPosition(float3 position);
	void Move(float3 direction);

	mat4 GetProjection()const;
	mat4 GetView() const;
	mat4 GetVP() const;
	float3 GetPos() const;

	bool Contains(FG::Vector2D  pos, FG::Vector2D size);
};