#pragma once
#include "Entity.h"
#include "Vector2D.h"
#include "BezierPath.h"

class BaseEnemy : public FG::Entity
{
public:
	enum MovementType
	{
		MoveStraight = 0,
		MoveCircular = 1,
		MoveSweep = 2,
		MoveWave = 3,
		MoveDoubleWave = 4,
	};

	enum BulletSpreadType
	{
		ShootForward = 0,
		ShootWave = 1,
		ShootCircle = 2,
		ShootTriple = 3,
		ShootDouble = 4,
		ShootDoubleWave = 5,
		ShootDoubleVertical = 6,
	};

	enum BulletColor
	{
		Light = 0,
		Dark = 1,
		Double = 2,
	};

	MovementType mt = MoveSweep;
	BulletSpreadType bs = ShootForward;
	BulletColor bc = Light;

	FG::Sprite sprite;
	FG::Vector2D position;

	//for curve animations
	std::vector<std::vector<FG::Vector2D>> animPath;
	int curveSamples = 0;
	int animSpeed = 25;
	float curvePosition = 0;

	//Functions to create animations
	void CreateSweepAnimation();
	void CreateCircularAnimation();
	void CreateWaveAnimation();
	void CreateDoubleWaveAnimation();

	BaseEnemy(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor);

	void Start(FG::Vector2D startPos);
	void Update(float deltaTime) override;
	void Render(Renderer* const camera) override;
	void OnCollision(Entity* other) override;
	void Disable() override;

	bool isColliding = false;
	SDL_Color notCollidingColor = { 0, 255, 0, 255 };
	SDL_Color CollidingColor = { 255, 0, 0, 255 };

private:
	float orbitSpeed = 1.0f;
	float orbitRadius = 2.0f;
	float angle = 1.0f;
	float timer = 0.2f;
	float accu = 0.0f;


	//For Brush bullet pattern
	int bulletInvert = 1.0f;

	//For Circle bullet pattern
	FG::Vector2D bulletDirection = { -1.0f,0.0f };
	FG::Vector2D bulletSpawnPosition = { -0.6f, 0.15f };
	float bulletSpeed = 10.0f;
	float bulletAngle = 0;
	float bulletRotateSpeed = 3.0f;

	FG::Vector2D centerPos;

	void Shoot(float deltaTime);
	void Move(float deltaTime);
};