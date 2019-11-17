#pragma once
#include "Bullet.h"
#include "Entity.h"

class Enemy : public FG::Entity
{
public:
	FG::Sprite sprite;
	FG::Vector2D position;
	Enemy();

	Enemy(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites);
	~Enemy() {}
	void Start() override;
	void Start(FG::Vector2D position, FG::Sprite sprite);

	void Update(float deltaTime) override;
	void Render(Renderer* const camera) override;
	void OnCollision(Entity* other) override;

	float timer = 0.15f;
	float accu = 0.0f;
};