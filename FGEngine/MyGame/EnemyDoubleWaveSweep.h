#pragma once
#include "BaseEnemy.h"

class EnemyDoubleWaveSweep : public BaseEnemy
{
public:
	EnemyDoubleWaveSweep(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor)
	{
	
	}
};

