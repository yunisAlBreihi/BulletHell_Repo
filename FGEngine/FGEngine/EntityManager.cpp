#include "EntityManager.h"
#include "Entity.h"
#include "Collision.h"

namespace FG
{
	EntityManager* EntityManager::instance = new EntityManager();

	EntityManager::EntityManager()
	{
	}

	EntityManager::~EntityManager()
	{
	}

	void EntityManager::Shutdown()
	{
		for (int i = 0; i < MAX_ENTITY_TYPES; i++)
		{
			if (entities[i].size() > 0)
			{
				if (entities[i][0] != nullptr)
				{
					delete[] entities[i][0];
					used[i] = 0;
					allocated[i] = 0;
				}
			}
			entities[i].clear();
		}
	}

	void EntityManager::Update(float deltaTime)
	{
		for (int i = 0; i < MAX_ENTITY_TYPES; i++)
		{
			for (int j = 0; j < allocated[i]; j++)
			{
				if (entities[i][j]->isActive) //TODO: Remove this, we want to keep contigous arrays so we don't need to branch here..
				{
					entities[i][j]->Update(deltaTime);
				}
			}
		}
	}

	void EntityManager::Render(Renderer* const renderer)
	{
		for (int i = 0; i < MAX_ENTITY_TYPES; i++)
		{
			for (int j = 0; j < allocated[i]; j++)
			{
				if (entities[i][j]->isActive)//TODO: Remove this, we want to keep contigous arrays so we don't need to branch here..
				{
					entities[i][j]->Render(renderer);
				}
			}
		}
	}

	void EntityManager::RemoveEntity(Entity* entity)
	{
		if (entity->isActive)
		{
			entities[entity->layer][entity->index]->Disable();
			intervals[entity->layer].FreeIndex(entity->index);
			used[entity->layer]--;
		}
	}


}
