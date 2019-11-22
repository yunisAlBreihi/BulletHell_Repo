#include "EnemySpawnParameters.h"

EnemySpawnParameters::EnemySpawnParameters(float timerMax, FG::Vector2D position) :timerMax(timerMax), position(position)
{
	timer = 0;
	intervalTimer = 0;
}
