#include "Enemy01.h"
#include "Camera.h"
#include "Sprite.h"
#include <SDL_render.h>
#include <cmath>

Enemy01::Enemy01(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites, BulletSpreadType bulletSpreadType, MovementType movementType)
	: sprite(sprite), position(position), bs(bulletSpreadType), mt(movementType)
{

}

void Enemy01::Start(FG::Vector2D startPos)
{
	position = startPos;
	centerPos = position;

	if (mt == Sweep)
	{
		CreateSweepAnimation();
	}
	else if (mt == Circular)
	{
		CreateCircularAnimation();
	}

	Entity::Start();
}

void Enemy01::Update(float deltaTime)
{
	Move(deltaTime);

	Shoot(deltaTime);
}

void Enemy01::Render(Renderer* const camera)
{
	camera->Render(position, sprite);
	//bullets.Render(camera);
}

void Enemy01::TestCollision(Entity* other)
{
	//bullets.TestCollision(other);
}

void Enemy01::DrawBoundingBox()
{
}

void Enemy01::RenderBullets(Renderer* const renderer)
{
//	bullets.Render(renderer);
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
		//	bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, bulletDirection.y });
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
		//	bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, bulletDirection.y });
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
		//	bullets.Shoot((position + bulletSpawnPosition), { bulletSpawnPosition.x, bulletSpawnPosition.y });

			accu = 0;
		}
	}

	if (bs == Triple)
	{
		accu += deltaTime;
		if (accu >= timer)
		{
		/*	bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, 0.2 });
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, 0 });
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, -0.2 });*/

			accu = 0;
		}
	}

	if (bs == Double)
	{
		accu += deltaTime;
		if (accu >= timer)
		{
			/*bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, 0.2 });
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, -0.2 });*/

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
		/*	bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, bulletDirection.y });
			bullets.Shoot((position + bulletSpawnPosition), { bulletDirection.x, -bulletDirection.y });*/

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
			/*bullets.Shoot((position + bulletSpawnPositionTop), { 0, -1 });
			bullets.Shoot((position + bulletSpawnPositionBot), { 0, 1 });*/

			accu = 0;
		}
	}

	/*bullets.Update(deltaTime);*/
}

void Enemy01::Move(float deltaTime)
{
	if (mt == Straight)
	{
		position.x -= speed * deltaTime;
	}
	else
	{
		if (curvePosition <= curveSamples)
		{
			position.x = animPath[0][curvePosition += animSpeed * deltaTime].x;
			position.y = animPath[0][curvePosition += animSpeed * deltaTime].y;
		}
	}
}

void Enemy01::CreateSweepAnimation()
{
	int currentPath = 0;
	FG::BezierPath* path = new FG::BezierPath();
	path->AddCurve({ FG::Vector2D(position.x,position.y),FG::Vector2D(position.x - 12.0f,position.y),FG::Vector2D(position.x - 12.0f, -position.y), FG::Vector2D(position.x,-position.y) }, curveSamples);

	animPath.push_back(std::vector<FG::Vector2D>());
	path->Sample(&animPath[currentPath]);
	delete path;

	curveSamples *= 1;
}

void Enemy01::CreateCircularAnimation()
{
	int currentPath = 0;
	FG::BezierPath* path = new FG::BezierPath();

	path->AddCurve({ FG::Vector2D(position.x,position.y),FG::Vector2D(position.x - 2.0f,position.y),FG::Vector2D(position.x - 4.0f, position.y), FG::Vector2D(position.x - 6.0f, position.y) }, curveSamples);
	path->AddCurve({ FG::Vector2D(position.x - 6.0f,position.y),FG::Vector2D(position.x - 7.5f,position.y),FG::Vector2D(position.x - 9.0f, position.y - 1.5f), FG::Vector2D(position.x - 9.0f, position.y - 3.0f) }, curveSamples);
	path->AddCurve({ FG::Vector2D(position.x - 9.0f,position.y - 3.0f),FG::Vector2D(position.x - 9.0f,position.y - 4.5f),FG::Vector2D(position.x - 7.5f, position.y - 6.0f), FG::Vector2D(position.x - 6.0f, position.y - 6.0f) }, curveSamples);
	path->AddCurve({ FG::Vector2D(position.x - 6.0f, position.y - 6.0f),FG::Vector2D(position.x - 4.5f,position.y - 6.0f),FG::Vector2D(position.x - 3.0f, position.y - 4.5f), FG::Vector2D(position.x - 3.0f, position.y - 3.0f) }, curveSamples);
	path->AddCurve({ FG::Vector2D(position.x - 3.0f, position.y - 3.0f),FG::Vector2D(position.x - 3.0f,position.y - 1.5f),FG::Vector2D(position.x - 4.5f, position.y), FG::Vector2D(position.x -6.0f, position.y) }, curveSamples);
	path->AddCurve({ FG::Vector2D(position.x - 6.0f, position.y),FG::Vector2D(position.x - 8.0f,position.y),FG::Vector2D(position.x - 10.0f, position.y), FG::Vector2D(position.x - 12.0f, position.y) }, curveSamples);


	animPath.push_back(std::vector<FG::Vector2D>());
	path->Sample(&animPath[currentPath]);
	delete path;

	curveSamples *= 6;
}