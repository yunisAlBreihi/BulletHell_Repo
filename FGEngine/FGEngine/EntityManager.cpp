#include "EntityManager.h"
#include "Entity.h"
#include "Collision.h"

namespace FG
{
	void EntityManager::Shutdown()
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


	void EntityManager::AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}
}
