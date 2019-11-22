#include "Bullet.h"
#include "Sprite.h"
#include "Camera.h"
#include <iostream>
#include "CollisionSystem.h"
#include "EntityManager.h"
#include "Player.h"
#include "BaseEnemy.h"
BaseBullet::BaseBullet()
{
	speed = 0;

	sprite.SetScale(FG::Vector2D(0.5f, 0.5f));	
	sprite.textureIndex = 0;
	sprite.spriteIndex = 0;
}



void BaseBullet::Update(float deltaTime)
{
	position.x += dir.x * speed * deltaTime;
	position.y += dir.y * speed * deltaTime;

	auto instance = CollisionSystem::GetInstance();
	instance->RegisterCollider(position, sprite.GetScale(), this, layer, true);

	if (position.x > 21.0f || position.x < -1.0f)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
}

void BaseBullet::Render(Renderer* const renderer)
{
	renderer->Render(position, sprite);
	//renderer->RenderQuad(position, sprite.GetScale(), Color(1.0f, 1.0f, 1.0f, 1.0f), Color());
}

LightBullet::LightBullet(FG::Sprite sprite)
{
	rotatingBullet = false;
	this->sprite = sprite;
	collidesWith = EntityLayers::GetEntityMask<BaseEnemy, Player>();
}

void LightBullet::Update(float deltaTime)
{
	position.x += dir.x * speed * deltaTime;
	position.y += dir.y * speed * deltaTime;
	if (position.x > 21 || position.x < -1 || position.y > 21 || position.y < -1)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
	auto instance = CollisionSystem::GetInstance();
	instance->RegisterCollider(position, sprite.GetScale(), this, layer, true);
}

void LightBullet::Start(const FG::Vector2D position, const FG::Vector2D direction, float speed, uint64_t collidesWith)
{
	Entity::Start();
	rotatedOneTime = false;
	this->dir = direction;
	this->position = position;
	this->speed = speed;
	this->collidesWith = collidesWith;

	rotatingBullet = false;
}

void LightBullet::Start(const FG::Vector2D position, const FG::Vector2D direction, float speed, uint64_t collidesWith, float rotation, float rotationRate)
{
	Entity::Start();
	rotatedOneTime = false;
	startRotation = M_PI;
	this->dir = direction;
	this->position = position;
	this->collidesWith = collidesWith;
	this->speed = speed;
	this->rotation = rotation;
	this->rotationRate = rotationRate;

	rotatingBullet = true;
}


void LightBullet::OnCollision(Entity* other)
{
	if (this->isActive)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
}

DarkBullet::DarkBullet(FG::Sprite sprite)
{

	this->sprite = sprite;
	collidesWith = EntityLayers::GetEntityMask<BaseEnemy, Player>();
}

void DarkBullet::Update(float deltaTime)
{

	position.x += dir.x * speed * deltaTime;
	position.y += dir.y * speed * deltaTime;
	if (position.x > 21 || position.x < -1 || position.y > 21 || position.y < -1)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
	auto instance = CollisionSystem::GetInstance();
	instance->RegisterCollider(position, sprite.GetScale(), this, layer, true);
}

void DarkBullet::Start(const FG::Vector2D position, const FG::Vector2D direction, float speed, uint64_t collidesWith)
{
	Entity::Start();
	rotatedOneTime = false;
	this->dir = direction;
	this->position = position;
	this->speed = speed;
	this->collidesWith = collidesWith;

	rotatingBullet = false;
}

void DarkBullet::Start(const FG::Vector2D position, const FG::Vector2D direction, float speed, uint64_t collidesWith, float rotation, float rotationRate)
{
	Entity::Start();
	rotatedOneTime = false;
	startRotation = M_PI;
	this->dir = direction;
	this->position = position;
	this->collidesWith = collidesWith;
	this->speed = speed;
	this->rotation = rotation;
	this->rotationRate = rotationRate;

	rotatingBullet = true;
}


void DarkBullet::OnCollision(FG::Entity* other)
{
	if (this->isActive)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
}