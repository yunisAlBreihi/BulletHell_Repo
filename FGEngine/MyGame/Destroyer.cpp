#include "Destroyer.h"
#include "EntityManager.h"
#include "Bullet.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Player.h"

Destroyer::Destroyer(FG::Sprite sprite)
{
	this->sprite = sprite;
}

void Destroyer::Start(FG::Vector2D position)
{
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

}

void Destroyer::Render(Renderer* const renderer)
{
	renderer->Render(position, sprite);
}

void Destroyer::OnCollision(FG::Entity* other)
{

}


