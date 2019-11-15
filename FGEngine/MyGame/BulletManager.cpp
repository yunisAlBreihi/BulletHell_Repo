#include "BulletManager.h"
#include "Sprite.h"
#include "Camera.h"
#include <iostream>
#include "Obstacle.h"
#include "CollisionSystem.h"
#include "Enemy.h"



BulletManager::BulletManager()
{
//	(void)static_cast<BaseBullet*>((T*)0);
	freeIndices = IntervalSet(0, 1);
	bullets = std::vector<BaseBullet*>();
	bullets.clear();
	for (int i = 0; i < 1; i++)
	{
		bullets.emplace_back(new BaseBullet());
		bullets[i]->Init(this, i, 10.0f);

		freeIndices.FreeIndex(i);
		bullets[i]->position.x = 0;
		bullets[i]->position.y = 0;
		bullets[i]->sprite = FG::Sprite();
	}
}

void BulletManager::Update(float deltaTime)
{

	auto instance = CollisionSystem::GetInstance();
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->active)
		{
			bullets[i]->Update(deltaTime);

			instance->RegisterCollider(bullets[i]->position, bullets[i]->sprite.GetScale(), bullets[i], true);
		}
	}
}

void BulletManager::Shoot(const FG::Vector2D& position, const FG::Vector2D& direction)
{
	int index = freeIndices.GetFirst();
	if (index != -1)
	{
		bullets[index]->active = true;
		bullets[index]->position = position;
		bullets[index]->dir = direction;
	}
}

void BulletManager::DisableBullet(int index)
{
	bullets[index]->active = false;
	freeIndices.FreeIndex(index);
}

void BulletManager::Render(Renderer* renderer)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->active)
		{
			bullets[i]->sprite.SetScale({ 0.5f, 0.5f });
			renderer->Render(bullets[i]->position, bullets[i]->sprite);
			renderer->RenderQuad(bullets[i]->position, bullets[i]->sprite.GetScale(), Color(), Color());
		}
	}
}

BaseBullet::BaseBullet()
{
	index = 0;
	speed = 0;
	bulletManager = nullptr;
	layer = EntityLayers::GetEntityLayer<BaseBullet>();
	collidesWith = EntityLayers::GetEntityMask<Obstacle, Enemy>();
}

void BaseBullet::Init(BulletManager* manager, int index, float speed)
{
	this->index = index;
	this->speed = speed;
	this->bulletManager = manager;
}

void BaseBullet::OnCollision(Entity* other)
{
	if (other->layer == EntityLayers::GetEntityLayer<Obstacle>() || other->layer == EntityLayers::GetEntityLayer<Enemy>())
	{
		bulletManager->DisableBullet(index);
	}
}

void BaseBullet::Update(float deltaTime)
{
	position.x += dir.x * speed * deltaTime;
	position.y += dir.y * speed * deltaTime;

	if (position.x > 5)
	{
		bulletManager->DisableBullet(index);
	}
}

LightBullet::LightBullet()
{
	layer = EntityLayers::GetEntityLayer<LightBullet>();
	collidesWith = EntityLayers::GetEntityMask<Obstacle, Enemy>();
}

void LightBullet::Update(float deltaTime)
{
	position.y += dir.x * speed * deltaTime;
	position.y += dir.y * speed * deltaTime;
	if (position.y > 10 || position.y < -10)
	{
		bulletManager->DisableBullet(index);
	}
}

void LightBullet::OnCollision(Entity* other)
{
	bulletManager->DisableBullet(index);
}
