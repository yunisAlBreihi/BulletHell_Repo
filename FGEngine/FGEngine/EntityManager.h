#pragma once

#include <vector>
#include "Renderer.h"
#include "EntityType.h"
#include <cassert>
#include "Intevals.h"
#include "Entity.h"
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
		

		void Shutdown();

		void Update(float deltaTime);
		void Render(Renderer*const renderer);

		template <typename T, typename... Args>
		void InitializeEntityArray(size_t count, Args&&...args);

		template <typename T, typename... Args>
		T* CreateEntity(Args&&...args);

		void RemoveEntity(Entity* entity);

	private:
		std::vector<Entity*> entities[MAX_ENTITY_TYPES];
		int used[MAX_ENTITY_TYPES] = {};
		int allocated[MAX_ENTITY_TYPES] = {};
		IntervalSet intervals[MAX_ENTITY_TYPES];
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
			entities[index][i]->Initialize(i);
		}
		intervals[index] = IntervalSet(0, count);
		allocated[index] = count;
	}

	template<typename T, typename... Args>
	inline T* EntityManager::CreateEntity(Args&&...args)
	{
		(void)static_cast<Entity*>((T*)0); //Check if the requested type is an entity
		uint64_t index = EntityLayers::GetEntityLayer<T>(); // get the entity type index
		assert(used[index] < allocated[index]); // make sure we're not using memory we haven't allocated
		auto i = intervals[index].GetFirst(); //intervals.GetFirst() consumes the left most index, i.e. the index closest to 0
		T* ret = dynamic_cast<T*>(entities[index][i]); 	///IF YOU CRASH HERE: There are not enough entities allocated
			//TODO: deal with out of bounds memory access if we're using too many entities
		ret->Start(args...); //call start function on created entity
		used[index]++;
		return ret;
	}
}

