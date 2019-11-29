#include "BezierCurveManager.h"
#include <iostream>

BezierCurveManager::BezierCurveManager()
{
	CreateSweepAnimation();
	CreateCircularAnimation();
	CreateWaveAnimation();
	CreateDoubleWaveAnimation();

}

void BezierCurveManager::CreateSweepAnimation()
{
	int currentPath = 0;
	FG::BezierPath path = FG::BezierPath();
	path.AddCurve({
		FG::Vector2D(position.x,position.y - 2.0f),
		FG::Vector2D(position.x - 4.0f,position.y - 2.0f),
		FG::Vector2D(position.x - 8.0f, position.y - 2.0f),
		FG::Vector2D(position.x - 12.0f,position.y - 2.0f) }, samples);
	path.AddCurve({
		FG::Vector2D(position.x - 12.0f,position.y - 2.0f),
		FG::Vector2D(position.x - 18.0f,position.y - 2.0f),
		FG::Vector2D(position.x - 18.0f, position.y + 2.0f),
		FG::Vector2D(position.x - 12.0f,position.y + 2.0f) }, samples + 30);
	path.AddCurve({
		FG::Vector2D(position.x - 12.0f,position.y + 2.0f),
		FG::Vector2D(position.x - 8.0f,position.y + 2.0f),
		FG::Vector2D(position.x - 4.0f, position.y + 2.0f),
		FG::Vector2D(position.x,position.y + 2.0f) }, samples);

	path.Sample(&sweepPath);

	//Sets which direction the enemy is moving after its done following the curve
	sweepDirection = 1;
}

void BezierCurveManager::CreateCircularAnimation()
{
	int currentPath = 0;
	FG::BezierPath path;

	// we can probably reuse these?
	// scale it to what our needs are
	// 

	path.AddCurve({
		FG::Vector2D(position.x,position.y),
		FG::Vector2D(position.x - 4.0f,position.y)
		,FG::Vector2D(position.x - 8.0f, position.y),
		FG::Vector2D(position.x - 12.0f, position.y) }, samples);
	path.AddCurve({
		FG::Vector2D(position.x - 12.0f,position.y),
		FG::Vector2D(position.x - 13.5f,position.y),
		FG::Vector2D(position.x - 15.0f, position.y - 1.5f),
		FG::Vector2D(position.x - 15.0f, position.y - 3.0f) }, samples);
	path.AddCurve({
		FG::Vector2D(position.x - 15.0f,position.y - 3.0f),
		FG::Vector2D(position.x - 15.0f,position.y - 4.5f),
		FG::Vector2D(position.x - 13.5f, position.y - 6.0f),
		FG::Vector2D(position.x - 12.0f, position.y - 6.0f) }, samples);
	path.AddCurve({
		FG::Vector2D(position.x - 12.0f, position.y - 6.0f),
		FG::Vector2D(position.x - 10.5f,position.y - 6.0f),
		FG::Vector2D(position.x - 9.0f, position.y - 4.5f),
		FG::Vector2D(position.x - 9.0f, position.y - 3.0f) }, samples);
	path.AddCurve({
		FG::Vector2D(position.x - 9.0f, position.y - 3.0f),
		FG::Vector2D(position.x - 9.0f,position.y - 1.5f),
		FG::Vector2D(position.x - 10.5f, position.y),
		FG::Vector2D(position.x - 12.0f, position.y) }, samples);
	path.AddCurve({
		FG::Vector2D(position.x - 12.0f, position.y),
		FG::Vector2D(position.x - 16.0f,position.y),
		FG::Vector2D(position.x - 20.0f, position.y),
		FG::Vector2D(position.x - 24.0f, position.y) }, samples);

	path.Sample(&circularPath);

	//Sets which direction the enemy is moving after its done following the curve
	circularDirection = -1;
}

void BezierCurveManager::CreateWaveAnimation()
{
	int currentPath = 0;
	FG::BezierPath path = FG::BezierPath();

	path.AddCurve({
		FG::Vector2D(position.x,position.y),
		FG::Vector2D(position.x - 12.0f,position.y - 10.0f),
		FG::Vector2D(position.x - 12.0f, position.y + 10.0f),
		FG::Vector2D(position.x - 24.0f, position.y) }, samples);
	path.Sample(&wavePath);

	//Sets which direction the enemy is moving after its done following the curve
	waveDirection = -1;
}

void BezierCurveManager::CreateDoubleWaveAnimation()
{
	int currentPath = 0;
	FG::BezierPath path = FG::BezierPath();


	path.AddCurve({
		FG::Vector2D(position.x,position.y),
		FG::Vector2D(position.x - 6.0f,position.y - 10.0f),
		FG::Vector2D(position.x - 6.0f, position.y + 10.0f),
		FG::Vector2D(position.x - 12.0f, position.y) }, samples);
	path.AddCurve({
		FG::Vector2D(position.x - 12.0f,position.y),
		FG::Vector2D(position.x - 18.0f,position.y - 10.0f),
		FG::Vector2D(position.x - 18.0f, position.y + 10.0f),
		FG::Vector2D(position.x - 24.0f, position.y) }, samples);

	path.Sample(&doubleWavePath);

	//Sets which direction the enemy is moving after its done following the curve
	doubleWaveDirection = -1;
}
