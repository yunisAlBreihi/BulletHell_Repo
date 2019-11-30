#pragma once
#include <SDL.h>
#include "Renderer.h"

namespace FG
{
	class DrawCurve
	{
	public:
		DrawCurve(Renderer* renderer);
		void DrawLine(FG::Vector2D vecA, FG::Vector2D vecB);

	private:
		Renderer* renderer = nullptr;
	};
}
