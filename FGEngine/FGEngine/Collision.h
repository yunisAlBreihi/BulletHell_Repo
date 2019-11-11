#pragma once

#include <SDL_rect.h>

namespace FG
{
	class Collision
	{
	public:
		// Axis aligned bounding box (AABB)
		static bool CheckAABBCollision(const SDL_Rect& a, const SDL_Rect& b);

	private:
		Collision() {}
		Collision(const Collision& other) {}
		~Collision() {}
	};
}
