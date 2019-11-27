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
BaseEnemy::BaseEnemy(FG::Vector2D position, FG::Sprite sprite, BulletSpreadType bulletSpreadType, MovementType movementType, BulletColor bulletColor)
	: sprite(sprite), position(position), bs(bulletSpreadType), mt(movementType), bc(bulletColor)
{
	health = 0;
	collidesWith = EntityLayers::GetEntityMask<DarkBullet, LightBullet, Player>();
	healthBarStepWidth = (sprite.GetScale().x / (MAX_HEALTH + 1));
	healthBarWidth = sprite.GetScale().x;
}

void BaseEnemy::Start(FG::Vector2D startPos)
{
	health = MAX_HEALTH;
	position = startPos;
	centerPos = position;
	curvePosition = 0;

	if (mt == MoveSweep)
	{
		CreateSweepAnimation();
	}
	else if (mt == MoveCircular)
	{
		CreateCircularAnimation();
	}
	else if (mt == MoveWave)
	{
		CreateWaveAnimation();
	}
	else if (mt == MoveDoubleWave)
	{
		CreateDoubleWaveAnimation();
	}

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
	Move(deltaTime);
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
	if (mt == MoveStraight)
	{
		position.x -= animSpeed * deltaTime;
	}
	else
	{
		if (curvePosition < animPath.size())
		{
			FG::Vector2D temp = animPath[curvePosition] - position;
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
			position.x += animSpeed * deltaTime * curveDirection;
		}
	}
	if (position.x < 0.0f || position.x > 30.0f)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
}

const static int samples = 10;
void BaseEnemy::CreateSweepAnimation()
{

	int currentPath = 0;
	FG::BezierPath path = FG::BezierPath();
	path.AddCurve({ 
		FG::Vector2D(position.x,position.y - 2.0f),
		FG::Vector2D(position.x - 4.0f,position.y - 2.0f),
		FG::Vector2D(position.x - 8.0f, position.y - 2.0f), 
		FG::Vector2D(position.x - 12.0f,position.y - 2.0f) }, samples);
	path.AddCurve({ 
		FG::Vector2D(position.x - 12.0f,position.y - 2.0f),
		FG::Vector2D(position.x - 18.0f,position.y - 2.0f),
		FG::Vector2D(position.x - 18.0f, position.y + 2.0f), 
		FG::Vector2D(position.x - 12.0f,position.y + 2.0f) }, samples + 30);
	path.AddCurve({ 
		FG::Vector2D(position.x - 12.0f,position.y + 2.0f),
		FG::Vector2D(position.x - 8.0f,position.y + 2.0f),
		FG::Vector2D(position.x - 4.0f, position.y + 2.0f), 
		FG::Vector2D(position.x,position.y + 2.0f) }, samples);

	path.Sample(&animPath);

	//Sets which direction the enemy is moving after its done following the curve
	curveDirection = 1;
}

void BaseEnemy::CreateCircularAnimation()
{
	int currentPath = 0;
	FG::BezierPath path;

	// we can probably reuse these?
	// scale it to what our needs are
	// 

	path.AddCurve({ 
		FG::Vector2D(position.x,position.y),
		FG::Vector2D(position.x - 4.0f,position.y)
		,FG::Vector2D(position.x - 8.0f, position.y), 
		FG::Vector2D(position.x - 12.0f, position.y) }, samples);
	path.AddCurve({
		FG::Vector2D(position.x - 12.0f,position.y),
		FG::Vector2D(position.x - 13.5f,position.y),
		FG::Vector2D(position.x - 15.0f, position.y - 1.5f), 
		FG::Vector2D(position.x - 15.0f, position.y - 3.0f) }, samples);
	path.AddCurve({ 
		FG::Vector2D(position.x - 15.0f,position.y - 3.0f),
		FG::Vector2D(position.x - 15.0f,position.y - 4.5f),
		FG::Vector2D(position.x - 13.5f, position.y - 6.0f), 
		FG::Vector2D(position.x - 12.0f, position.y - 6.0f) }, samples);
	path.AddCurve({ 
		FG::Vector2D(position.x - 12.0f, position.y - 6.0f),
		FG::Vector2D(position.x - 10.5f,position.y - 6.0f),
		FG::Vector2D(position.x - 9.0f, position.y - 4.5f), 
		FG::Vector2D(position.x - 9.0f, position.y - 3.0f) }, samples);
	path.AddCurve({ 
		FG::Vector2D(position.x - 9.0f, position.y - 3.0f),
		FG::Vector2D(position.x - 9.0f,position.y - 1.5f),
		FG::Vector2D(position.x - 10.5f, position.y), 
		FG::Vector2D(position.x - 12.0f, position.y) }, samples);
	path.AddCurve({ 
		FG::Vector2D(position.x - 12.0f, position.y),
		FG::Vector2D(position.x - 16.0f,position.y),
		FG::Vector2D(position.x - 20.0f, position.y), 
		FG::Vector2D(position.x - 24.0f, position.y) }, samples);

	path.Sample(&animPath);

	//Sets which direction the enemy is moving after its done following the curve
	curveDirection = -1;
}

void BaseEnemy::CreateWaveAnimation()
{
	int currentPath = 0;
	FG::BezierPath path = FG::BezierPath();

	path.AddCurve({ 
		FG::Vector2D(position.x,position.y),
		FG::Vector2D(position.x - 12.0f,position.y - 10.0f),
		FG::Vector2D(position.x - 12.0f, position.y + 10.0f), 
		FG::Vector2D(position.x - 24.0f, position.y) }, samples);
	path.Sample(&animPath);

	//Sets which direction the enemy is moving after its done following the curve
	curveDirection = -1;
}

void BaseEnemy::CreateDoubleWaveAnimation()
{
	int currentPath = 0;
	FG::BezierPath path = FG::BezierPath();


	path.AddCurve({ 
		FG::Vector2D(position.x,position.y),
		FG::Vector2D(position.x - 6.0f,position.y - 10.0f),
		FG::Vector2D(position.x - 6.0f, position.y + 10.0f), 
		FG::Vector2D(position.x - 12.0f, position.y) }, samples);
	path.AddCurve({ 
		FG::Vector2D(position.x - 12.0f,position.y),
		FG::Vector2D(position.x - 18.0f,position.y - 10.0f),
		FG::Vector2D(position.x - 18.0f, position.y + 10.0f), 
		FG::Vector2D(position.x - 24.0f, position.y) }, samples);

	path.Sample(&animPath);

	//Sets which direction the enemy is moving after its done following the curve
	curveDirection = -1;
}