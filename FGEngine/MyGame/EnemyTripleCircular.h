#pragma once
#include "BaseEnemy.h"
class EnemyTripleCircular : public BaseEnemy
{
public:
	EnemyTripleCircular(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor)
	{
	}
};

