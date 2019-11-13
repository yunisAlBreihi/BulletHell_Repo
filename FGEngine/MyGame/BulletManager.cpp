#include "BulletManager.h"
#include "Sprite.h"
#include "Camera.h"
#include <iostream>
#include "Obstacle.h"
#include "CollisionSystem.h"
BulletManager::BulletManager(size_t count, FG::Sprite sprite)
{
	freeIndices = IntervalSet(0, count);
	bullets.resize(count);
	for (int i = 0; i < count; i++)
	{
		freeIndices.Add(i);
		bullets[i].position.x = 0;
		bullets[i].position.y = 0;
		bullets[i].sprite = sprite;
		bullets[i].bulletManager = this;
		bullets[i].index = i;
	}
}

void BulletManager::Update(float deltaTime)
{
	auto instance = CollisionSystem::GetInstance();
	auto collisionLayer = instance->GetObjectLayer<_Bullet>();
	auto collidesWith = instance->GetCollisionMask<Obstacle>();
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].active)
		{
			bullets[i].position.x += bullets[i].dir.x * 10.0f * deltaTime;
			bullets[i].position.y += bullets[i].dir.y * 10.0f * deltaTime;
			instance->RegisterCollider(bullets[i].position, bullets[i].sprite.size, &bullets[i], true, collisionLayer, collidesWith);
			//instance->RegisterCollider(FG::Vector2D(bullets[i].position.x, bullets[i].position.y), bullets[i].sprite.size, &bullets[i], true);
		}
	}
}

void BulletManager::Shoot(const FG::Vector2D& position, const FG::Vector2D& direction)
{
	int index = freeIndices.GetFirst();
	if (index != -1)
	{
		bullets[index].active = true;
		bullets[index].position = position;
		bullets[index].dir = direction;
	}
}

void BulletManager::DisableBullet(int index)
{
	bullets[index].active = false;
	freeIndices.Add(index);
}

void BulletManager::Render(Renderer* renderer)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].active)
		{
			bullets[i].sprite.size = { 0.5f, 0.5f };
			renderer->Render(bullets[i].position, bullets[i].sprite);
		}
	}
}

void _Bullet::OnCollision(Entity* other)
{
	bulletManager->DisableBullet(index);
}
