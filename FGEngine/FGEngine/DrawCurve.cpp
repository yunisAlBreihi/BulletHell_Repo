#include "DrawCurve.h"

namespace FG
{
	DrawCurve::DrawCurve(Renderer* renderer) : renderer(renderer) {}

	void DrawCurve::DrawLine(FG::Vector2D vecA, FG::Vector2D vecB)
	{
		renderer->RenderLine(vecA, vecB, {255,0,0},0.1f);
	}
}