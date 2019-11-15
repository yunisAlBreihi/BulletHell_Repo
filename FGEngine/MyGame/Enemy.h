#pragma once
#include "BulletManager.h"
#include "Entity.h"

class Enemy : public FG::Entity
{
	BulletManager* bullets;
public:
	FG::Sprite sprite;
	FG::Vector2D position;
	Enemy() 
	{
		bullets = new BulletManager(BaseBullet(), 10, FG::Sprite());
		std::cout << "Hello!" << std::endl;
		this->sprite.SetScale({ 1.0f, 1.0f });
	}
	Enemy(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites);

	void Start() override;
	void Start(FG::Vector2D position);

	void Update(float deltaTime) override;
	void Render(Renderer* const camera) override;
	virtual void TestCollision(Entity* other) override;
	void DrawBoundingBox();
	SDL_Rect GetColliderRectangle();
	void RenderBullets(Renderer* const camera);

	bool isColliding = false;
	SDL_Color notCollidingColor = { 0, 255, 0, 255 };
	SDL_Color CollidingColor = { 255, 0, 0, 255 };

	float timer = 0.15f;
	float accu = 0.0f;
};