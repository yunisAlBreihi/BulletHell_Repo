#include "DrawCurve.h"

namespace FG
{
	DrawCurve::DrawCurve(SDL_Renderer* renderer) : renderer(renderer) {}

	void DrawCurve::DrawLine(float startX, float StartY, float endX, float endY)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer, startX, StartY, endX, endY);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	}
}