#pragma once
#include "BulletManager.h"
#include "Entity.h"
#include "Vector2D.h"

class Enemy01 : public FG::Entity
{
public:
	BulletManager bullets;

	enum BulletSpread 
	{
		Brush,
		Circle,
		Triple,
		Forward,
		UpDown,
	};

	BulletSpread bs = Brush;

	FG::Sprite sprite;
	FG::Vector2D position;
	Enemy01(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites);

	void Update(float deltaTime) override;
	void Render(Renderer* const camera) override;
	virtual void TestCollision(Entity* other) override;
	void DrawBoundingBox();
	SDL_Rect GetColliderRectangle();
	void RenderBullets(Renderer* const camera);

	void BulletSpread(float deltaTime);

	bool isColliding = false;
	SDL_Color notCollidingColor = { 0, 255, 0, 255 };
	SDL_Color CollidingColor = { 255, 0, 0, 255 };

private:
	float orbitSpeed = 1.0f;
	float orbitRadius = 2.0f;
	float angle = 1.0f;
	float timer = 0.2f;
	float accu = 0.0f;
	float speed = 0.5f;
	FG::Vector2D bulletDirection = { -0.5,0 };
	int bulletInvert = 1.0f;

	FG::Vector2D centerPos = position;

	void Shoot(float deltaTime);
};