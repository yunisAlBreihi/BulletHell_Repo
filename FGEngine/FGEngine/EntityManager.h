#pragma once

#include <vector>
#include "Renderer.h"

namespace FG
{
	class Entity;
	class Camera;
	class EntityManager
	{
	public:
		void Shutdown();

		void Update(float deltaTime);
		void Render(Renderer*const renderer);

		void AddEntity(Entity* entity);

	private:
		std::vector<Entity*> entities;
	};
}

