#include "BulletManager.h"
#include "Sprite.h"
#include "Camera.h"
#include <iostream>
#include "CollisionSystem.h"
BulletManager::BulletManager(size_t count, FG::Sprite* sprite)
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
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].active)
		{
			bullets[i].position.x += bullets[i].dir.x * 150.0f * deltaTime;
			bullets[i].position.y += bullets[i].dir.y * 150.0f * deltaTime;
			instance->RegisterCollider(FG::Vector2D(bullets[i].position.x, bullets[i].position.y), bullets[i].sprite->size, &bullets[i], true);
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

void BulletManager::Render(FG::Camera* camera)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].active)
		{
			bullets[i].sprite->Render(camera, bullets[i].position);
		}
	}
}

void BulletManager::_Bullet::OnCollision(Entity* other)
{
	bulletManager->DisableBullet(index);
}
