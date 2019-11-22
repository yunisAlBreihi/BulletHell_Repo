#pragma once
#include <vector>
#include "Vector2D.h"
#include "Spawner.h"

class EnemySpawnParameters
{
public:

	EnemySpawnParameters(float timerMax, FG::Vector2D position);

	float intervalTimer;
	float timerMax;
	float timer;

	FG::Vector2D position;
};

