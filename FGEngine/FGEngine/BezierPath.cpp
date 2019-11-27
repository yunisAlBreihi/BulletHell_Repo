#include "BezierPath.h"

namespace FG
{

	void BezierPath::AddCurve(BezierCurve curve, int samples)
	{
		mCurves.push_back(curve);
		mSamples.push_back(samples);
	}

	void BezierPath::Sample(std::vector<Vector2D>* samplePath)
	{
		for (int i = 0; i < mCurves.size(); i++)
		{
			for (float t = 0; t <= 1.0f; t += 1.0f / mSamples[i])
			{
				samplePath->push_back(mCurves[i].CalculateCurvePoint(t));
			}
		}
	}

}