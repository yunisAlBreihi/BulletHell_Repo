#pragma once
#include "BaseEnemy.h"

class EnemyWaveStraight : public BaseEnemy
{
public:
	EnemyWaveStraight(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor) :
		BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor)
	{

	}
};

