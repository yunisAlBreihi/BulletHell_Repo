#pragma once
#include "BaseEnemy.h"

class EnemyWaveStraight : public BaseEnemy
{
public:
	EnemyWaveStraight(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager) :
		BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor,curveManager)
	{
		animSpeed = 5;
	}
};

