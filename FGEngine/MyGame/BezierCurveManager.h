#pragma once
#include "BezierPath.h"
#include "Vector2D.h"

class BezierCurveManager
{
public:

	enum Animation
	{
		Sweep,
		Circular,
		Wave,
		DoubleWave,
	};

	BezierCurveManager();

	//std::vector<FG::Vector2D> GetAnimation(Animation animation);
	//int GetDirection(Animation animation);

private:

	void CreateSweepAnimation();
	void CreateCircularAnimation();
	void CreateWaveAnimation();
	void CreateDoubleWaveAnimation();

public:
	std::vector<FG::Vector2D> sweepPath;
	std::vector<FG::Vector2D> circularPath;
	std::vector<FG::Vector2D> wavePath;
	std::vector<FG::Vector2D> doubleWavePath;

	int sweepDirection = 0;
	int circularDirection = 0;
	int waveDirection = 0;
	int doubleWaveDirection = 0;

private:
	const int samples = 30;

	FG::Vector2D position = { 0.0f,0.0f };

};

