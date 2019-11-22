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
		void Initialize(const uint64_t index, const uint64_t layer)
		{
			this->index = index;
			this->layer = layer;
			this->isActive = false;
		}

	public:
		friend class FG::EntityManager;
		virtual ~Entity() {}

		//This function is called when CreateEntity is called
		virtual void Start() { isActive = true; }
		
		//this function is called when RemoveEntity is called
		virtual void Disable() { isActive = false; }

		//this function is called every frame
		virtual void Update(float deltaTime) {}
		
		//this function is called every frame, after update
		virtual void Render(Renderer* const renderer) {}

		//this function is called if the entity has registered a collider with the collisionSystem
		virtual void OnCollision(Entity* other) { std::cout << "collided!" << std::endl; }
		
		uint64_t collidesWith;
		bool isActive;
		uint64_t layer;
	};
}
