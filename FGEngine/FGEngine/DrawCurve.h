#pragma once
#include <SDL.h>

namespace FG
{
	class DrawCurve
	{
	public:
		DrawCurve(SDL_Renderer* renderer);


		void DrawLine(float startX, float StartY, float endX, float endY);

	private:
		SDL_Renderer* renderer = nullptr;
	};
}
