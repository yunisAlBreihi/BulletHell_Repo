#include "BaseEnemy.h"
#include "Camera.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Player.h"
#include "EntityManager.h"
#include <SDL_render.h>
#include <cmath>
#include "CollisionSystem.h"
#include "BasicRandom.h"
#include "float3.h"
#include "WeaponPickup.h"
BaseEnemy::BaseEnemy(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor, BezierCurveManager* curveManager)
	: sprite(sprite), position(position), bs(bulletSpreadType), mt(movementType), bc(bulletColor)
{
	this->curveManager = curveManager;

	health = 0;
	collidesWith = EntityLayers::GetEntityMask<DarkBullet, LightBullet, Player>();
	healthBarStepWidth = (sprite.GetScale().x / (MAX_HEALTH + 1));
	healthBarWidth = sprite.GetScale().x;
}
void BaseEnemy::Start(FG::Vector2D startPos)
{
	health = MAX_HEALTH;
	position = startPos;
	positionOffset = startPos;
	centerPos = position;
	curvePosition = 0;

	Entity::Start();
}

void BaseEnemy::Update(float deltaTime)
{
	if (health <= 0)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
		if (BasicRandom::Range(0, 100) > 50)
		{
			auto it = FG::EntityManager::Instance()->CreateEntity<WeaponPickup>(position);
		}
		return;
	}

	if (mt == MoveStraight)
	{
		Move(deltaTime);
	}

	else if (mt == MoveSweep)
	{
		MovePath(deltaTime, curveManager->sweepPath, curveManager->sweepDirection);
	}
	else if (mt == MoveCircular)
	{
		MovePath(deltaTime, curveManager->circularPath, curveManager->circularDirection);
	}
	else if (mt == MoveWave)
	{
		MovePath(deltaTime, curveManager->wavePath, curveManager->waveDirection);
	}
	else if (mt == MoveDoubleWave)
	{
		MovePath(deltaTime, curveManager->doubleWavePath, curveManager->doubleWaveDirection);
	}

	Shoot(deltaTime);
	auto it = CollisionSystem::GetInstance();
	it->RegisterCollider(position, sprite.GetScale(), this, EntityLayers::GetEntityLayer<BaseEnemy>(), true);
}

void BaseEnemy::Render(Renderer* const camera)
{
	camera->Render(position, sprite);

	//health bar
	//TODO: Error handle xScale == 0
	camera->RenderQuad(position, FG::Vector2D(healthBarWidth, healthBarHeight), Color(0.3f, 0.3f, 0.3f, 1.0f), Color(0.3f, 0.3f, 0.3f, 1.0f));
	camera->RenderQuad(position, FG::Vector2D(healthBarStepWidth * health, healthBarHeight), Color(1.0f, 0.3f, 0.3f, 1.0f), Color(1.0f, 0.3f, 0.3f, 1.0f));
}

void BaseEnemy::Disable()
{
	isActive = false;
	animPath.clear();
}

void BaseEnemy::OnCollision(Entity* other)
{
	if (isActive && other->layer == EntityLayers::GetEntityLayer<DarkBullet>() && bc == Light)
	{
		health--;
	}
	else if (isActive && other->layer == EntityLayers::GetEntityLayer<LightBullet>() && bc == Dark)
	{
		health--;
	}
	else if (isActive && (other->layer == EntityLayers::GetEntityLayer<LightBullet>() ||
		other->layer == EntityLayers::GetEntityLayer<DarkBullet>()) && bc == Both)
	{
		health--;
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
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, bulletDirection, bulletSpeed, EntityLayers::GetEntityMask<Player>());
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
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, bulletDirection, bulletSpeed, EntityLayers::GetEntityMask<Player>());
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
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, bulletSpawnPosition, bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}

		if (bs == ShootTriple)
		{
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, 0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, bulletDirection, bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());

				accu = 0;
			}
		}

		if (bs == ShootDouble)
		{
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, 0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
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
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, bulletDirection.y), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -bulletDirection.y), bulletSpeed, EntityLayers::GetEntityMask<Player>());

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
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPositionTop, FG::Vector2D(0, -1), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPositionBot, FG::Vector2D(0, 1), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}
	}
	else if (bc == Both)
	{
		if (bs == ShootTriple)
		{
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, 0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, bulletDirection, bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());

				accu = 0;
			}
		}

		if (bs == ShootDouble)
		{
			accu += deltaTime;
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, 0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, -0.2f), bulletSpeed, EntityLayers::GetEntityMask<Player>());
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
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPosition, FG::Vector2D(bulletDirection.x, bulletDirection.y), bulletSpeed, EntityLayers::GetEntityMask<Player>());
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
				FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position + bulletSpawnPositionTop, FG::Vector2D(0, -1), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position + bulletSpawnPositionBot, FG::Vector2D(0, 1), bulletSpeed, EntityLayers::GetEntityMask<Player>());
				accu = 0;
			}
		}
	}
}

void BaseEnemy::Move(float deltaTime)
{
	position.x -= animSpeed * deltaTime;
}

void BaseEnemy::MovePath(float deltaTime, std::vector<FG::Vector2D> path, int direction)
{

	if (curvePosition < path.size())
	{
		FG::Vector2D temp = (path[curvePosition] + positionOffset) - position;
		float3 movement = float3(temp.x, temp.y, 0);

		if (movement.x < 0.01f && movement.x > -0.01f && movement.y < 0.01f && movement.y > -0.01f)
		{
			curvePosition += 1;
		}
		if (movement.x != 0 || movement.y != 0)
		{
			movement = float3Util::normalize(movement);
			movement *= deltaTime;
			position.x += movement.x * 2.0f;
			position.y += movement.y * 2.0f;
		}
	}
	else
	{
		position.x += animSpeed * deltaTime * direction;
	}
}