#include "EntityManager.h"
#include "Entity.h"
#include "Collision.h"

namespace FG
{
	void EntityManager::Shutdown()
	{
		for (int i = 0; i < MAX_ENTITY_TYPES; i++)
		{
			entities[i].clear();
		}
	}

	void EntityManager::Update(float deltaTime)
	{
		for (int i = 0; i < MAX_ENTITY_TYPES; i++)
		{
			for (int j = 0; j < allocated[i]; j++)
			{
				if (entities[i][j]->isActive)
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
			for (int j = 0; j < used[i]; j++)
			{
				if (entities[i][j]->isActive)
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
