#pragma once
#include "BulletManager.h"
#include "Entity.h"
#include "Vector2D.h"

class Enemy01 : public FG::Entity
{
public:
	BulletManager bullets;

	enum MovementType
	{
		Straight,
		Circular,
		Sweep,
	};

	enum BulletSpreadType
	{
		Forward,
		Wave,
		Circle,
		Triple,
		Double,
		DoubleWave,
		VerticalDouble,
	};

	MovementType mt = Sweep;
	BulletSpreadType bs = DoubleWave;


	FG::Sprite sprite;
	FG::Vector2D position;
	Enemy01(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites, BulletSpreadType bulletSpreadType);

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
	FG::Vector2D bulletDirection = { -0.5f,0.0f };
	FG::Vector2D bulletSpawnPosition = { -0.6f, 0.15f };
	float bulletAngle = 0;
	float bulletRotateSpeed = 3.0f;

	FG::Vector2D centerPos = position;

	void Shoot(float deltaTime);
	void Move(float deltaTime);
};