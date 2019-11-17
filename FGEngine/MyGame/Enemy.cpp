#include "Enemy.h"
#include "Camera.h"
#include "Sprite.h"

#include "EntityManager.h"
#include "CollisionSystem.h"
#include "Player.h"
#include "Obstacle.h"
Enemy::Enemy()
{
	layer = EntityLayers::GetEntityLayer<Enemy>();
	collidesWith = EntityLayers::GetEntityMask<BaseBullet>();
	this->sprite.SetScale({ 1.0f, 1.0f });
}
Enemy::Enemy(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites)
	: sprite(sprite), position(position)
{
	layer = EntityLayers::GetEntityLayer<Enemy>();
	collidesWith = EntityLayers::GetEntityMask<BaseBullet>();
}

void Enemy::Start()
{
	Entity::Start();
}

void Enemy::Start(FG::Vector2D position, FG::Sprite sprite)
{
	Entity::Start();
	this->position = position;
	this->sprite = sprite;
	//this->bullets->sprite = bulletsSprite;
}

void Enemy::Update(float deltaTime)
{
	accu += deltaTime;
	if (accu >= timer)
	{
		auto bullet = FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position, FG::Vector2D(-1, 0), 3.0f, EntityLayers::GetEntityLayer<Enemy>());
		accu = 0;
	}
	auto it = CollisionSystem::GetInstance();
	it->RegisterCollider(position, sprite.GetScale(), this, true);
}

void Enemy::Render(Renderer* const camera)
{
	camera->RenderQuad(position, sprite.GetScale(), Color(), Color());
	camera->Render(position, sprite);
}

void Enemy::OnCollision(Entity* other)
{
	if (isActive)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
}