#include "EntityManager.h"
#include "Entity.h"
#include "Collision.h"

namespace FG
{
	/*void EntityManager::Shutdown()
	{
		for (auto it = entities.begin(); it != entities.end(); it++)
		{
			delete *it;
		}
		entities.clear();
	}

	void EntityManager::Update(float deltaTime)
	{
		for (auto entity : entities)
		{
			entity->Update(deltaTime);
		}
	}

	void EntityManager::Render(Renderer*const renderer)
	{
		for (auto entity : entities)
		{
			entity->Render(renderer);
		}
	}

	void EntityManager::RemoveEntity(Entity* entity)
	{

	}*/

	EntityManager::EntityManager()
	{
		for (int i = 0; i < 64; i++)
		{
			used[i] = 0;
			entities = new Entity*[64];
		}
	}

	EntityManager::~EntityManager()
	{
	}

	void EntityManager::Shutdown()
	{
	}

	void EntityManager::Update(float deltaTime)
	{
		for (int i = 0; i < 64; i++)
		{
			for (int j = 0; j < used[i]; j++)
			{
				(entities[i] + j)->Update(deltaTime);
			}
		}
	}

	void EntityManager::Render(Renderer* const renderer)
	{
		for (int i = 0; i < 64; i++)
		{
			for (int j = 0; j < used[i]; j++)
			{
				(entities[i] + j)->Render(renderer);
			}
		}
	}

	void EntityManager::RemoveEntity(Entity* entity)
	{
	}

}
