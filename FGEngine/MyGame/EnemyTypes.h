#pragma once
#include "BaseEnemy.h"

#pragma region EnemyTripleCircular
class EnemyTripleCircularL : public BaseEnemy
{
public:
	EnemyTripleCircularL(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{
	}
};

class EnemyTripleCircularD : public BaseEnemy
{
public:
	EnemyTripleCircularD(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{
	}
};

class EnemyTripleCircularB : public BaseEnemy
{
public:
	EnemyTripleCircularB(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{
	}
};
#pragma endregion

#pragma region EnemyForwardDoubleWave

class EnemyForwardDWaveL : public BaseEnemy
{
public:
	EnemyForwardDWaveL(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager) :
		BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{
		animSpeed = 80;
	}
};

class EnemyForwardDWaveD : public BaseEnemy
{
public:
	EnemyForwardDWaveD(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager) :
		BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{
		animSpeed = 80;
	}
};
#pragma endregion

#pragma region EnemyDoubleWaveSweep

class EnemyDWaveSweepL : public BaseEnemy
{
public:
	EnemyDWaveSweepL(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{

	}
};

class EnemyDWaveSweepD : public BaseEnemy
{
public:
	EnemyDWaveSweepD(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{

	}
};

class EnemyDWaveSweepB : public BaseEnemy
{
public:
	EnemyDWaveSweepB(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{

	}
};

#pragma endregion

#pragma region EnemyDoubleVerticalWave

class EnemyDVerticalWaveL : public BaseEnemy
{
public:
	EnemyDVerticalWaveL(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{
		animSpeed = 2;
	}
};

class EnemyDVerticalWaveD : public BaseEnemy
{
public:
	EnemyDVerticalWaveD(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{
		animSpeed = 7;
	}
};

class EnemyDVerticalWaveB : public BaseEnemy
{
public:
	EnemyDVerticalWaveB(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{
		animSpeed = 7;
	}
	//EnemyDVerticalWaveB(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, BulletColor bulletColor, bool moveStraight = false)
	//	: BaseEnemy(position, sprite, bulletSpreadType, bulletColor, moveStraight)
	//{
	//	animSpeed = 7;
	//}
};

#pragma endregion

#pragma region EnemyCircleStraight

class EnemyCircleStraightL : public BaseEnemy
{
public:
	EnemyCircleStraightL(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{
		animSpeed = 5;
	}
};

class EnemyCircleStraightD : public BaseEnemy
{
public:
	EnemyCircleStraightD(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{
		animSpeed = 5;
	}
};

#pragma endregion

#pragma region EnemyWaveStraight

class EnemyWaveStraightL : public BaseEnemy
{
public:
	EnemyWaveStraightL(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{
		animSpeed = 5;
	}
};

class EnemyWaveStraightD : public BaseEnemy
{
public:
	EnemyWaveStraightD(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
		: BaseEnemy(position, sprite, bulletSpreadType, movementType, bulletColor, curveManager)
	{
		animSpeed = 3;
	}
};

#pragma endregion