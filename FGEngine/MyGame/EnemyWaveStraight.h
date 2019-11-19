#pragma once
#include "BaseEnemy.h"

class EnemyWaveStraight : public BaseEnemy
{
public:
	EnemyWaveStraight(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprite, BulletSpreadType bulletSpreadType, MovementType movementType);
	
};

