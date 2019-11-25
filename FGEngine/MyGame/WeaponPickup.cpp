#include "WeaponPickup.h"
#include "CollisionSystem.h"
#include "EntityManager.h"
#include "Player.h"
WeaponPickup::WeaponPickup(FG::Sprite sprite)
{
	this->sprite = sprite;
	collidesWith = EntityLayers::GetEntityMask<Player>();
}
void WeaponPickup::Start(FG::Vector2D position)
{
	FG::Entity::Start();
	this->position = position;
	timeToLive = 15;
}

void WeaponPickup::Update(float deltaTime)
{
	//TTL
	timeToLive -= deltaTime;
	if (timeToLive < 0)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
	}
	CollisionSystem::GetInstance()->RegisterCollider(position, sprite.GetScale(), this, layer, true);
}

void WeaponPickup::Render(Renderer* const renderer)
{
	renderer->Render(position, sprite);
}

void WeaponPickup::OnCollision(Entity* other)
{
	if (isActive)
	{
		if (other->layer == EntityLayers::GetEntityLayer<Player>())
		{
			FG::EntityManager::Instance()->RemoveEntity(this);
		}
	}
}
