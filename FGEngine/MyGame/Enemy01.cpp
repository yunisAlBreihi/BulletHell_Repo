#include "Enemy01.h"
#include "Camera.h"
#include "Sprite.h"
#include <SDL_render.h>
#include <cmath>

Enemy01::Enemy01(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites, BulletSpreadType bulletSpreadType)
	: sprite(sprite), position(position), bullets(BaseBullet(), 150, bulletsSprites), bs(bulletSpreadType)
{
}

void Enemy01::Update(float deltaTime)
{
	Move(deltaTime);

	Shoot(deltaTime);
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

void Enemy01::Shoot(float deltaTime)
{
	if (bs == Forward)
	{
		accu += deltaTime;
		if (accu >= timer)
		{
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, bulletDirection.y });
			accu = 0;
		}
	}

	if (bs == Wave)
	{
		bulletDirection.y += deltaTime * bulletInvert;

		if (bulletDirection.y < -0.85f || bulletDirection.y > 0.85f)
		{
			bulletInvert *= -1;
		}
		accu += deltaTime;
		if (accu >= timer)
		{
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, bulletDirection.y });
			accu = 0;
		}
	}

	if (bs == Circle)
	{
		bulletAngle += bulletRotateSpeed * deltaTime;

		bulletSpawnPosition.x = 1.0f * cos(bulletAngle);
		bulletSpawnPosition.y = 1.0f * sin(bulletAngle);

		accu += deltaTime;
		timer = .075f;
		if (accu >= timer)
		{
			bullets.Shoot((position + bulletSpawnPosition), { bulletSpawnPosition.x, bulletSpawnPosition.y });

			accu = 0;
		}
	}

	if (bs == Triple)
	{
		accu += deltaTime;
		if (accu >= timer)
		{
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, 0.2 });
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, 0 });
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, -0.2 });

			accu = 0;
		}
	}

	if (bs == Double)
	{


		accu += deltaTime;
		if (accu >= timer)
		{
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, 0.2 });
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, -0.2 });

			accu = 0;
		}
	}

	if (bs == DoubleWave)
	{
		bulletDirection.y += 0.5f * deltaTime * bulletInvert;

		if (bulletDirection.y < 0.0f || bulletDirection.y > 0.6f)
		{
			bulletInvert *= -1;
		}

		accu += deltaTime;
		if (accu >= timer)
		{
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, bulletDirection.y });
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, -bulletDirection.y });

			accu = 0;
		}
	}

	if (bs == VerticalDouble)
	{
		FG::Vector2D bulletSpawnPositionTop = { 0.2f,-0.4f };
		FG::Vector2D bulletSpawnPositionBot = { 0.2f,0.8f };

		accu += deltaTime;
		if (accu >= timer)
		{
			bullets.Shoot((position + bulletSpawnPositionTop), { 0, -1 });
			bullets.Shoot((position + bulletSpawnPositionBot), { 0, 1 });

			accu = 0;
		}
	}

	bullets.Update(deltaTime);
}

void Enemy01::Move(float deltaTime)
{
	if (mt == Straight)
	{
		position.x -= speed * deltaTime;
	}

	if (mt == Circular)
	{
		speed = 0.5f;

		centerPos.x -= speed * deltaTime;

		angle += orbitSpeed * deltaTime;
		position.x = centerPos.x + orbitRadius * cos(angle);
		position.y = centerPos.y + orbitRadius * sin(angle);
	}

	if (mt == Sweep)
	{
		speed = 0.5f;
		centerPos.x -= speed * deltaTime;

		angle += orbitSpeed * deltaTime;
		position.x = centerPos.x + orbitRadius * cos(angle);
		position.y = centerPos.y + orbitRadius* sin(angle)/2;
	}

	if (centerPos.x < -5.5f)
	{
		centerPos.x = 5.5f;
	}
}
