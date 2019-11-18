#include "Bullet.h"
#include "Sprite.h"
#include "Camera.h"
#include <iostream>
#include "Obstacle.h"
#include "CollisionSystem.h"
#include "Enemy.h"
#include "EntityManager.h"

BaseBullet::BaseBullet()
{
	speed = 0;
	layer = EntityLayers::GetEntityLayer<BaseBullet>();
	collidesWith = EntityLayers::GetEntityMask<Obstacle, Enemy>();
	sprite.SetScale(FG::Vector2D(0.5f, 0.5f));	
	sprite.textureIndex = 0;
	sprite.spriteIndex = 0;
}

void BaseBullet::Start(const FG::Vector2D position, const FG::Vector2D direction, float speed, uint64_t collidesWith)
{
	Entity::Start();
	this->dir = direction;
	this->position = position;
	this->speed = speed;
	this->collidesWith = collidesWith;
}


void BaseBullet::OnCollision(Entity* other)
{
	if (this->isActive)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
}

void BaseBullet::Update(float deltaTime)
{
	position.x += dir.x * speed * deltaTime;
	position.y += dir.y * speed * deltaTime;
	auto instance = CollisionSystem::GetInstance();
	instance->RegisterCollider(position, sprite.GetScale(), this, true);

	//out of bounds check
	if (position.x > 20.0f || position.x < -1.0f)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
}

void BaseBullet::Render(Renderer* const renderer)
{
	renderer->Render(position, sprite);
	renderer->RenderQuad(position, sprite.GetScale(), Color(), Color());
}

LightBullet::LightBullet()
{
	layer = EntityLayers::GetEntityLayer<LightBullet>();
	collidesWith = EntityLayers::GetEntityMask<Obstacle, Enemy>();
}

void LightBullet::Update(float deltaTime)
{
	position.x += dir.x * speed * deltaTime;
	position.y += dir.y * speed * deltaTime;
	if (position.y > 10 || position.y < -10)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
}

void LightBullet::Start(const FG::Vector2D position, const FG::Vector2D direction, float speed, uint64_t collidesWith)
{
	Entity::Start();
	this->dir = direction;
	this->position = position;
	this->speed = speed;
	this->collidesWith = collidesWith;
}

void LightBullet::OnCollision(Entity* other)
{
	if (this->isActive)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
}
