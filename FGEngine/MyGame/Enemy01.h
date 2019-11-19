#pragma once
#include "Entity.h"
#include "Vector2D.h"
#include "BezierPath.h"

class Enemy01 : public FG::Entity
{
public:
	enum MovementType
	{
		Straight=0,
		Circular=1,
		Sweep=2,
	};

	enum BulletSpreadType
	{
		Forward=0,
		Wave=1,
		Circle=2,
		Triple=3,
		Double=4,
		DoubleWave=5,
		DoubleVertical=6,
	};

	MovementType mt = Sweep;
	BulletSpreadType bs = Forward;

	FG::Sprite sprite;
	FG::Vector2D position;

	//for curve animations
	std::vector<std::vector<FG::Vector2D>> animPath;
	int curveSamples = 0;
	int animSpeed = 25;
	float curvePosition = 0;
	void CreateSweepAnimation();
	void CreateCircularAnimation();

	Enemy01(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites, BulletSpreadType bulletSpreadType, MovementType movementType);

	void Start(FG::Vector2D startPos);
	void Update(float deltaTime) override;
	void Render(Renderer* const camera) override;
	virtual void TestCollision(Entity* other) override;
	void DrawBoundingBox();
	SDL_Rect GetColliderRectangle();
	void RenderBullets(Renderer* const camera);

	bool isColliding = false;
	SDL_Color notCollidingColor = { 0, 255, 0, 255 };
	SDL_Color CollidingColor = { 255, 0, 0, 255 };

private:
	float orbitSpeed = 1.0f;
	float orbitRadius = 2.0f;
	float angle = 1.0f;
	float timer = 0.2f;
	float accu = 0.0f;
	float speed = 2.0f;

	
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