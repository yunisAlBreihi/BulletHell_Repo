#pragma once

#include <SDL_rect.h>
#include <iostream>

namespace FG
{
	class Camera;
	class Entity
	{
	public:
		virtual ~Entity() {}

		virtual void Update(float deltaTime) {}
		virtual void Render(Camera* const camera) {}
		virtual void OnCollision(Entity* other) { std::cout << "collided!" << std::endl; }
		virtual void TestCollision(Entity* other) {}
	};
}
