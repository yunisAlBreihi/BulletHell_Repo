#pragma once
#include "Vector2D.h"
#include "BezierCurve.h"
#include <SDL.h>
#include <vector>

namespace FG 
{
	class BezierPath 
	{
	private:
		std::vector<BezierCurve> mCurves;
		std::vector<int> mSamples;

	public:
		BezierPath();
		~BezierPath();

		void AddCurve(BezierCurve curve, int samples);

		void Sample(std::vector<Vector2D>* samplePath);
	};
}