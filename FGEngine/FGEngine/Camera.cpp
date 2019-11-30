//#include "Camera.h"
//#include "Logger.h"
//#include "Window.h"
//
//#include <cassert>
//#include <SDL_render.h>
//
//bool FG::Camera::Initialize(Window* window)
//{
//	assert(window);
//	ownerWindow = window;
//	renderer = SDL_CreateRenderer(window->GetInternalWindow(), -1, SDL_RENDERER_ACCELERATED);
//	if (!renderer)
//	{
//		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
//		return false;
//	}
//
//	return true;
//}
//
//void FG::Camera::Shutdown()
//{
//	if (renderer)
//	{
//		SDL_DestroyRenderer(renderer);
//		renderer = nullptr;
//	}
//}
//
//void FG::Camera::StartRenderFrame()
//{
//	SDL_RenderClear(renderer);
//}
//
//void FG::Camera::EndRenderFrame()
//{
//	SDL_RenderPresent(renderer);
//}
//
//void FG::Camera::SetColor(const SDL_Color& color)
//{
//	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
//}
//
//SDL_Color FG::Camera::GetColor()
//{
//	Uint8 red = 0;
//	Uint8 blue = 0;
//	Uint8 green = 0;
//	Uint8 alpha = 0;
//	SDL_GetRenderDrawColor(renderer, &red, &green, &blue, &alpha);
//	return { red, green, blue, alpha };
//}


#include "camera.h"
#include "InputManager.h"
#include "Window.h"
#undef near
#undef far


float Camera::zoom = 1.0f;

const float zoomSpeed = 0.5f;
const float movementSpeed = 3.0f;

Camera::Camera(float3 position, float fov, float near, float far, float zoom)
{
	Camera::zoom = zoom;
	this->near = near;
	this->fov = fov;
	this->far = far;
	this->position = float3(position);
	lookAt = this->position + float3(0, 0, 1);
	 mat4Util::lookAt(view, position, lookAt, {0, 1, 0});
	//projection = mat4Util::ortho(-zoom, zoom, -zoom, zoom, near, far);
}

#include <iostream>
void Camera::Update(float dt, FG::Vector2D look)
{
	position = float3(look.x, look.y, -1);
	lookAt = position;
	mat4Util::lookAt(view, lookAt, lookAt + float3(0, 0, 1), float3(0, 1, 0));
	projection = mat4Util::ortho(zoom, 0, 0, -zoom * FG::Window::aspectRatio, near, far);
}

void Camera::SetPosition(float3 position)
{
	this->position = position;
}

void Camera::Move(float3 direction)
{
	position += direction;
}

mat4 Camera::GetProjection() const
{
	return projection;
}

mat4 Camera::GetView() const
{
	return view;
}

mat4 Camera::GetVP() const
{
	return view * projection;
}

float3 Camera::GetPos() const
{
	return position;
}

float Camera::GetZoom()
{
	return 0.0f;
}

bool Camera::Contains(FG::Vector2D p, FG::Vector2D size)
{
	FG::Vector2D pos = FG::Vector2D(p.x + position.x, p.y + position.y);
	if (pos.x - size.x > -10 && pos.x + size.x < 10)
	{
		if (pos.y + size.y > 10 && pos.y - size.y < 10)
		{
			return true;
		}
	}
	return false;
}
