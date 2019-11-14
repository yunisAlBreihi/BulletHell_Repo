#include "Enemy01.h"
#include "Camera.h"
#include "Sprite.h"
#include <SDL_render.h>
#include <cmath>

Enemy01::Enemy01(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites)
	: sprite(sprite), position(position), bullets(BaseBullet(), 150, bulletsSprites)
{ 

}

void Enemy01::Update(float deltaTime)
{
	centerPos.x -= speed * deltaTime;

	angle += orbitSpeed * deltaTime;
	position.x = centerPos.x + orbitRadius * cos(angle);
	position.y = centerPos.y*1.75f + orbitRadius * sin(angle);

	if (centerPos.x < -5.5f)
	{
		centerPos.x = 5.5f;
	}

	BulletSpread(deltaTime);
}

void Enemy01::Render(Renderer* const camera)
{
	camera->Render(position, sprite);
	bullets.Render(camera);
}

void Enemy01::TestCollision(Entity* other)
{
	bullets.TestCollision(other);
}

void Enemy01::DrawBoundingBox()
{
}

void Enemy01::RenderBullets(Renderer* const renderer)
{
	bullets.Render(renderer);
}

SDL_Rect Enemy01::GetColliderRectangle()
{
	return { 0,0,0,0 };
}

void Enemy01::BulletSpread(float deltaTime) 
{
	

	if (bs == Brush)
	{
		Shoot(deltaTime);

		bulletDirection.y += 1.0f * deltaTime * bulletInvert;

		if (bulletDirection.y < -0.85f || bulletDirection.y > 0.85f)
		{
			bulletInvert *= -1;
		}
	}
	
	bullets.Update(deltaTime);
	
	if (bs == Triple) 
	{
		Shoot(deltaTime);
	}
}

void Enemy01::Shoot(float deltaTime)
{
	accu += deltaTime;
	if (accu >= timer)
	{
		bullets.Shoot((position + FG::Vector2D(-1, 0)), { bulletDirection.x, bulletDirection.y });
		accu = 0;
	}
}