#pragma once
#include <cmath>
#include "Vector2D.h"

namespace FG
{
	struct BezierCurve
	{
		FG::Vector2D p0;
		FG::Vector2D p1;
		FG::Vector2D p2;
		FG::Vector2D p3;

		Vector2D CalculateCurvePoint(float t)
		{
			float tt = t * t;
			float ttt = tt * t;
			float u = 1.0f - t;
			float uu = u * u;
			float uuu = uu * u;

			Vector2D point = (p0 * uuu) + (p1 * 3 * uu * t) + (p2 * 3 * u * tt) + (p3 * ttt);
			return point;
		}
	};
}