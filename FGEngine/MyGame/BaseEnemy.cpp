#include "BaseEnemy.h"
#include "Camera.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Player.h"
#include "EntityManager.h"
#include <SDL_render.h>
#include <cmath>
#include "CollisionSystem.h"

BaseEnemy::BaseEnemy(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor)
	: sprite(sprite), position(position), bs(bulletSpreadType), mt(movementType), bc(bulletColor)
{

}

void BaseEnemy::Start(FG::Vector2D startPos)
{
	position = startPos;
	centerPos = position;

	if (mt == MoveSweep)
	{
		CreateSweepAnimation();
	}
	else if (mt == MoveCircular)
	{
		CreateCircularAnimation();
	}

	Entity::Start();
}

void BaseEnemy::Update(float deltaTime)
{
	Move(deltaTime);

	Shoot(deltaTime);
}

void BaseEnemy::Render(Renderer* const camera)
{
	camera->Render(position, sprite);
	//bullets.Render(camera);
}

void BaseEnemy::TestCollision(Entity* other)
{
	//bullets.TestCollision(other);
}

void BaseEnemy::OnCollision(Entity* other)
{
	if (isActive)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
}



void BaseEnemy::Shoot(float deltaTime)
{
	if (bc == Light)
	{
		if (bs == ShootForward)
		{
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, bulletDirection, bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}

		if (bs == ShootWave)
		{
			bulletDirection.y += deltaTime * bulletInvert;

			if (bulletDirection.y < -0.85f || bulletDirection.y > 0.85f)
			{
				bulletInvert *= -1;
			}
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, bulletDirection, bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}

		if (bs == ShootCircle)
		{
			bulletAngle += bulletRotateSpeed * deltaTime;

			bulletSpawnPosition.x = 1.0f * cos(bulletAngle);
			bulletSpawnPosition.y = 1.0f * sin(bulletAngle);

			accu += deltaTime;
			timer = .075f;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, bulletSpawnPosition, bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}

		if (bs == ShootTriple)
		{
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, 0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, bulletDirection, bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());

				accu = 0;
			}
		}

		if (bs == ShootDouble)
		{
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, 0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}

		if (bs == ShootDoubleWave)
		{
			bulletDirection.y += 0.5f * deltaTime * bulletInvert;

			if (bulletDirection.y < 0.0f || bulletDirection.y > 0.6f)
			{
				bulletInvert *= -1;
			}

			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, bulletDirection.y), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -bulletDirection.y), bulletSpeed, EntityLayers::GetEntityMask<Player>());

				accu = 0;
			}
		}

		if (bs == ShootDoubleVertical)
		{
			FG::Vector2D bulletSpawnPositionTop = { 0.2f,-0.4f };
			FG::Vector2D bulletSpawnPositionBot = { 0.2f,0.8f };

			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPositionTop, FG::Vector2D(0, -1), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPositionBot, FG::Vector2D(0, 1), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}
	}
	else if (bc == Dark)
	{
		if (bs == ShootForward)
		{
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, bulletDirection, bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}

		if (bs == ShootWave)
		{
			bulletDirection.y += deltaTime * bulletInvert;

			if (bulletDirection.y < -0.85f || bulletDirection.y > 0.85f)
			{
				bulletInvert *= -1;
			}
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, bulletDirection, bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}

		if (bs == ShootCircle)
		{
			bulletAngle += bulletRotateSpeed * deltaTime;

			bulletSpawnPosition.x = 1.0f * cos(bulletAngle);
			bulletSpawnPosition.y = 1.0f * sin(bulletAngle);

			accu += deltaTime;
			timer = .075f;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, bulletSpawnPosition, bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}

		if (bs == ShootTriple)
		{
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, 0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, bulletDirection, bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());

				accu = 0;
			}
		}

		if (bs == ShootDouble)
		{
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, 0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}

		if (bs == ShootDoubleWave)
		{
			bulletDirection.y += 0.5f * deltaTime * bulletInvert;

			if (bulletDirection.y < 0.0f || bulletDirection.y > 0.6f)
			{
				bulletInvert *= -1;
			}

			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, bulletDirection.y), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -bulletDirection.y), bulletSpeed, EntityLayers::GetEntityMask<Player>());

				accu = 0;
			}
		}

		if (bs == ShootDoubleVertical)
		{
			FG::Vector2D bulletSpawnPositionTop = { 0.2f,-0.4f };
			FG::Vector2D bulletSpawnPositionBot = { 0.2f,0.8f };

			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPositionTop, FG::Vector2D(0, -1), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPositionBot, FG::Vector2D(0, 1), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}
	}
	else if (bc == Double)
	{
		if (bs == ShootTriple)
		{
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, 0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, bulletDirection, bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());

				accu = 0;
			}
		}

		if (bs == ShootDouble)
		{
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, 0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}

		if (bs == ShootDoubleWave)
		{
			bulletDirection.y += 0.5f * deltaTime * bulletInvert;

			if (bulletDirection.y < 0.0f || bulletDirection.y > 0.6f)
			{
				bulletInvert *= -1;
			}

			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, bulletDirection.y), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -bulletDirection.y), bulletSpeed, EntityLayers::GetEntityMask<Player>());

				accu = 0;
			}
		}

		if (bs == ShootDoubleVertical)
		{
			FG::Vector2D bulletSpawnPositionTop = { 0.2f,-0.4f };
			FG::Vector2D bulletSpawnPositionBot = { 0.2f,0.8f };

			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position + bulletSpawnPositionTop, FG::Vector2D(0, -1), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPositionBot, FG::Vector2D(0, 1), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}
	}
}

void BaseEnemy::Move(float deltaTime)
{
	if (mt == MoveStraight)
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

void BaseEnemy::CreateSweepAnimation()
{
	int currentPath = 0;
	FG::BezierPath* path = new FG::BezierPath();
	path->AddCurve({ FG::Vector2D(position.x,position.y - 4.0f),FG::Vector2D(position.x - 4.0f,position.y - 4.0f),FG::Vector2D(position.x - 8.0f, position.y - 4.0f), FG::Vector2D(position.x - 12.0f,position.y - 4.0f) }, 100);
	path->AddCurve({ FG::Vector2D(position.x - 12.0f,position.y - 4.0f),FG::Vector2D(position.x - 18.0f,position.y - 4.0f),FG::Vector2D(position.x - 18.0f, position.y + 4.0f), FG::Vector2D(position.x - 12.0f,position.y + 4.0f) }, 130);
	path->AddCurve({ FG::Vector2D(position.x - 12.0f,position.y + 4.0f),FG::Vector2D(position.x - 8.0f,position.y + 4.0f),FG::Vector2D(position.x - 4.0f, position.y + 4.0f), FG::Vector2D(position.x,position.y + 4.0f) }, 100);

	animPath.push_back(std::vector<FG::Vector2D>());
	path->Sample(&animPath[currentPath]);
	delete path;

	//This needs to be the same as the sum of samples on the AddCurve functions
	curveSamples = 330;
}

void BaseEnemy::CreateCircularAnimation()
{
	int currentPath = 0;
	FG::BezierPath* path = new FG::BezierPath();

	path->AddCurve({ FG::Vector2D(position.x,position.y),FG::Vector2D(position.x - 4.0f,position.y),FG::Vector2D(position.x - 8.0f, position.y), FG::Vector2D(position.x - 12.0f, position.y) }, 100);
	path->AddCurve({ FG::Vector2D(position.x - 12.0f,position.y),FG::Vector2D(position.x - 13.5f,position.y),FG::Vector2D(position.x - 15.0f, position.y - 1.5f), FG::Vector2D(position.x - 15.0f, position.y - 3.0f) }, 43);
	path->AddCurve({ FG::Vector2D(position.x - 15.0f,position.y - 3.0f),FG::Vector2D(position.x - 15.0f,position.y - 4.5f),FG::Vector2D(position.x - 13.5f, position.y - 6.0f), FG::Vector2D(position.x - 12.0f, position.y - 6.0f) }, 43);
	path->AddCurve({ FG::Vector2D(position.x - 12.0f, position.y - 6.0f),FG::Vector2D(position.x - 10.5f,position.y - 6.0f),FG::Vector2D(position.x - 9.0f, position.y - 4.5f), FG::Vector2D(position.x - 9.0f, position.y - 3.0f) }, 43);
	path->AddCurve({ FG::Vector2D(position.x - 9.0f, position.y - 3.0f),FG::Vector2D(position.x - 9.0f,position.y - 1.5f),FG::Vector2D(position.x - 10.5f, position.y), FG::Vector2D(position.x - 12.0f, position.y) }, 43);
	path->AddCurve({ FG::Vector2D(position.x - 12.0f, position.y),FG::Vector2D(position.x - 16.0f,position.y),FG::Vector2D(position.x - 20.0f, position.y), FG::Vector2D(position.x - 24.0f, position.y) }, 100);


	animPath.push_back(std::vector<FG::Vector2D>());
	path->Sample(&animPath[currentPath]);
	delete path;

	//This needs to be the same as the sum of samples on the AddCurve functions
	curveSamples = 372;
}