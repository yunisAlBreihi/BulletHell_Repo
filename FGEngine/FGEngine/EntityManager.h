#pragma once

#include <vector>
#include "Renderer.h"
#include "EntityType.h"
#include <cassert>
#include "Entity.h"
#include <deque>
namespace FG
{
#define MAX_ENTITY_TYPES 64 

	class Entity;
	class Camera;
	class EntityManager
	{
		EntityManager();
		static EntityManager* instance;
	public:

		static EntityManager* Instance()
		{
			if (instance == nullptr) {
				instance = new EntityManager();
			}
			return instance;
		}
		
		~EntityManager();


		void Shutdown();

		void Update(float deltaTime);
		void Render(Renderer*const renderer);

		template <typename T, typename... Args>
		void InitializeEntityArray(size_t count, Args&&...args);

		template <typename T, typename... Args>
		T* CreateEntity(Args&&...args);

		template <typename T, typename... Args>
		T* CreateEntity(T type, Args&&...args);

		template <typename T>
		int GetUsedCount();

		void RemoveEntity(Entity* entity);

	private:
		std::vector<Entity*> entities[MAX_ENTITY_TYPES];
		int allocated[MAX_ENTITY_TYPES] = {};
		int used[MAX_ENTITY_TYPES] = {};
		std::deque<uint32_t> freeIndices[MAX_ENTITY_TYPES];
	};


	//TODO: Create arrays instead of individual objects
	template<typename T, typename... Args>
	inline void EntityManager::InitializeEntityArray(size_t count, Args&&...args)
	{
		(void)static_cast<Entity*>((T*)0);
		uint64_t index = EntityLayers::GetEntityLayer<T>();
		entities[index].resize(count);

		void* raw_memory = operator new[](count * sizeof(T));
		T* ptr = static_cast<T*>(raw_memory);

		for (int i = 0; i < count; i++)
		{
			new(&ptr[i])T(args...);
			entities[index][i] = static_cast<Entity*>(&ptr[i]);
			entities[index][i]->Initialize(i, index);
			freeIndices[index].push_back(i);
		}
		allocated[index] = count;
		used[index] = 0;
	}

	template<typename T, typename... Args>
	inline T* EntityManager::CreateEntity(Args&&...args)
	{
		(void)static_cast<Entity*>((T*)0); //Check if the requested type is an entity
		uint64_t index = EntityLayers::GetEntityLayer<T>(); // get the entity type index
		if (used[index] < allocated[index])
		{
			uint32_t i = freeIndices[index].front();
			freeIndices[index].pop_front();
			T* ret = dynamic_cast<T*>(entities[index][i]); 	///IF YOU CRASH HERE: There are not enough entities allocated
				//TODO: deal with out of bounds memory access if we're using too many entities
			used[index]++;
			ret->Start(args...); //call start function on created entity
			return ret;
		}
		return nullptr;
	}

	template<typename T, typename ...Args>
	inline T* EntityManager::CreateEntity(T type, Args&& ...args)
	{
		return NULL;
	}
	template<typename T>
	inline int EntityManager::GetUsedCount()
	{
		(void)static_cast<Entity*>((T*)0); //Check if the requested type is an entity
		uint64_t index = EntityLayers::GetEntityLayer<T>(); // get the entity type index
		return used[index];
	}
}

