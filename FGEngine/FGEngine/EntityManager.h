#pragma once

#include <vector>
#include "Renderer.h"
#include "EntityType.h"

namespace FG
{
	class Entity;
	class Camera;
	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();
		void Shutdown();

		void Update(float deltaTime);
		void Render(Renderer*const renderer);

		template <typename T>
		void InitializeEntityArray(size_t count);

		template <typename T>
		T* CreateEntity();

		void RemoveEntity(Entity* entity);



	private:
		Entity** entities;
		int used[64];
		int allocated[64];
	};



	template<typename T>
	inline void EntityManager::InitializeEntityArray(size_t count)
	{
		(void)static_cast<Entity*>((T*)0);
		uint64_t index = EntityLayers::GetEntityLayer<T>();
		entities[index] = new T[count];
		allocated[index] = 0;
	}

	template<typename T>
	inline T* EntityManager::CreateEntity()
	{
		(void)static_cast<Entity*>((T*)0);
		uint64_t index = EntityLayers::GetEntityLayer<T>();
		T* ret = dynamic_cast<T*>(entities[index]) + used[index];
		used[index]++;
		return ret;
	}
}

