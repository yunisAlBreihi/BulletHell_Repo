#include "Destroyer.h"
#include "EntityManager.h"
#include "Bullet.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CollisionSystem.h"
#include "Player.h"
#include "BaseEnemy.h"
Destroyer::Destroyer(FG::Sprite sprite)
{
	this->sprite = sprite;	
	collidesWith = EntityLayers::GetEntityMask<DarkBullet, LightBullet, Player>();
	healthBarStepWidth = (sprite.GetScale().x / (MAX_HEALTH + 1));
	healthBarWidth = sprite.GetScale().x;
}

void Destroyer::Start(FG::Vector2D position)
{
	health = MAX_HEALTH;
	direction = 1.0f;
	spawnAccu = 0;
	reverse = false;
	this->position = position;
	isActive = true;
}

void Destroyer::Disable()
{  
	isActive = false; 
}

void Destroyer::Update(float deltaTime)
{
	if (health <= 0)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
		return;
	}
	spawnAccu += deltaTime;
	spinSpeed += deltaTime;
	auto instance = FG::EntityManager::Instance();
	float baseAngle = spinSpeed * direction;
	if (spawnAccu >= spawnRate)
	{
		for (int i = 0; i < projectileCount; i++)
		{
			float angleOffset = M_PI_2 * (((float)i) / projectileCount);
			instance->CreateEntity<LightBullet>(position,
				FG::Vector2D(std::clamp(std::cos(angleOffset + baseAngle), -1.0f, 1.0f), std::clamp(std::sin(angleOffset + baseAngle), -1.0f, 1.0f)),
				projectileSpeed, EntityLayers::GetEntityMask<Player>(), baseAngle + angleOffset, 1.0f);
		}
	
		baseAngle = spinSpeed * -direction;

		for (int i = 0; i < projectileCount; i++)
		{

			float angleOffset = M_PI_2 * (((float)i) / projectileCount);
		
			instance->CreateEntity<LightBullet>(position,
				FG::Vector2D(std::clamp(std::cos(angleOffset + baseAngle), -1.0f, 1.0f), std::clamp(std::sin(angleOffset + baseAngle), -1.0f, 1.0f)),
				projectileSpeed, EntityLayers::GetEntityMask<Player>(), baseAngle + angleOffset, 1.0f);
		}

		baseAngle = spinSpeed * direction;

		for (int i = 0; i < projectileCount; i++)
		{
			float angleOffset = M_PI_2 * (((float)i) / projectileCount);
			instance->CreateEntity<LightBullet>(position + FG::Vector2D(0, 2),
				FG::Vector2D(std::clamp(std::cos(angleOffset + baseAngle), -1.0f, 1.0f), std::clamp(std::sin(angleOffset + baseAngle), -1.0f, 1.0f)),
				projectileSpeed, EntityLayers::GetEntityMask<Player>(), baseAngle + angleOffset, 1.0f);
		}

		baseAngle = spinSpeed * -direction;

		for (int i = 0; i < projectileCount; i++)
		{

			float angleOffset = M_PI_2 * (((float)i) / projectileCount);

			instance->CreateEntity<LightBullet>(position + FG::Vector2D(0, 2),
				FG::Vector2D(std::clamp(std::cos(angleOffset + baseAngle), -1.0f, 1.0f), std::clamp(std::sin(angleOffset + baseAngle), -1.0f, 1.0f)),
				projectileSpeed, EntityLayers::GetEntityMask<Player>(), baseAngle + angleOffset, 1.0f);
		}
		spawnAccu = 0;
	}

	CollisionSystem::GetInstance()->RegisterCollider(position, sprite.GetScale(), this, EntityLayers::GetEntityLayer<BaseEnemy>(), true);
}

void Destroyer::Render(Renderer* const renderer)
{
	renderer->Render(position, sprite);
	const float healthBarHeight = 0.15f;
	//TODO: Error handle xScale == 0
	renderer->RenderQuad(position, FG::Vector2D(healthBarWidth, healthBarHeight), Color(0.3f, 0.3f, 0.3f, 1.0f), Color(0.3f, 0.3f, 0.3f, 1.0f));
	renderer->RenderQuad(position, FG::Vector2D(healthBarStepWidth * health, healthBarHeight), Color(1.0f, 0.3f, 0.3f, 1.0f), Color(1.0f, 0.3f, 0.3f, 1.0f));
}

void Destroyer::OnCollision(FG::Entity* other)
{
	health--;
}


