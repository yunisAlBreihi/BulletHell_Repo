#pragma once

#include <SDL_rect.h>
#include <iostream>
#include "Renderer.h"
#include <stdint.h>
namespace FG
{
	class EntityManager;
	class Camera;
	class Entity
	{
	private:

		uint64_t index;

	public:
		friend class FG::EntityManager;

		void Initialize(const uint64_t index, const uint64_t layer)
		{
			this->index = index;
			this->layer = layer;
			this->isActive = false;
		}
		virtual ~Entity() {}

		virtual void Start() { isActive = true; }
		virtual void Disable() { isActive = false; }

		virtual void Update(float deltaTime) {}
		virtual void Render(Renderer* const renderer) {}
		virtual void OnCollision(Entity* other) { std::cout << "collided!" << std::endl; }
		virtual void TestCollision(Entity* other) {}
		
		uint64_t collidesWith;
		bool isActive;
		uint64_t layer;
	};
}
