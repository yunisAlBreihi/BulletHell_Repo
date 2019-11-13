#pragma once

#include <SDL_rect.h>
#include <iostream>
#include "Renderer.h"
#include <stdint.h>
namespace FG
{
	class Camera;
	class Entity
	{
	public:
		virtual ~Entity() {}

		virtual void Update(float deltaTime) {}
		virtual void Render(Renderer* const renderer) {}
		virtual void OnCollision(Entity* other) { std::cout << "collided!" << std::endl; }
		virtual void TestCollision(Entity* other) {}
		uint64_t layer;
		uint64_t collidesWith;
	};
}
