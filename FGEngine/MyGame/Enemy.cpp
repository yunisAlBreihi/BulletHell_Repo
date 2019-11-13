#include "Enemy.h"
#include "Camera.h"
#include "Sprite.h"
#include <SDL_render.h>
Enemy::Enemy(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites)
	: sprite(sprite), position(position), bullets(BulletManager(LightBullet(), 30, bulletsSprites)) { }

void Enemy::Update(float deltaTime)
{
	accu += deltaTime;
	if (accu >= timer)
	{
		bullets.Shoot(position + FG::Vector2D(0, 100), FG::Vector2D(0, 10));
		accu = 0;
	}
	bullets.Update(deltaTime);
}

void Enemy::Render(Renderer* const camera)
{
	camera->Render(position, sprite);
}

void Enemy::TestCollision(Entity* other)
{
	bullets.TestCollision(other);
}

void Enemy::RenderBullets(Renderer *const renderer)
{
	bullets.Render(renderer);
}

