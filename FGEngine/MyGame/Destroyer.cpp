#include "Destroyer.h"
#include "EntityManager.h"
#include "Bullet.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "CollisionSystem.h"
#include "Player.h"
#include "BaseEnemy.h"
Destroyer::Destroyer(FG::Sprite lightSprite, FG::Sprite darkSprite)
{

	usingLight = true;
	this->lightSprite = lightSprite;
	this->darkSprite = darkSprite;
	this->currentSprite = lightSprite;	
	collidesWith = EntityLayers::GetEntityMask<DarkBullet, LightBullet, Player>();
	healthBarStepWidth = (currentSprite.GetScale().x / (MAX_HEALTH + 1));
	healthBarWidth = currentSprite.GetScale().x;
}

void Destroyer::Start(FG::Vector2D position)
{
	animationTimer = BasicTimer(0.03f);
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
	animationTimer.Update(deltaTime);
	if (animationTimer.IsReady())
	{
		currentSprite.spriteIndex++;
		if (currentSprite.spriteIndex > 3)
		{
			currentSprite.spriteIndex = 0;
		}
		animationTimer.Use();
	}
	if (health <= 0)
	{
		FG::EntityManager::Instance()->RemoveEntity(this);
		return;
	}

	spawnAccu += deltaTime;
	spinSpeed += deltaTime;
	reverseAccu += deltaTime;

	if (reverseAccu >= 3.14f)
	{
		usingLight = !usingLight;
		currentSprite.textureIndex = usingLight ? lightSprite.textureIndex : darkSprite.textureIndex;
		reverseAccu = 0;
	}
	auto instance = FG::EntityManager::Instance();
	float baseAngle = spinSpeed * direction;
	if (spawnAccu >= spawnRate)
	{
		for (int i = 0; i < projectileCount; i++)
		{
			float angleOffset = 2.0f * M_PI * (((float)i) / projectileCount);
			Shoot(instance, position + currentSprite.GetScale() * 0.33f, baseAngle, angleOffset);
		}

		//baseAngle = spinSpeed * direction;

		//for (int i = 0; i < projectileCount; i++)
		//{
		//	float angleOffset = M_PI * (((float)i) / projectileCount);
		//	Shoot(instance, position + FG::Vector2D(1, 0), baseAngle, angleOffset);
		//}

		//baseAngle = spinSpeed * -direction;

		//for (int i = 0; i < projectileCount; i++)
		//{
		//	float angleOffset = M_PI * (((float)i) / projectileCount);
		//	Shoot(instance, position + FG::Vector2D(1, 0), baseAngle, angleOffset);
		//}
		spawnAccu = 0;
	}

	CollisionSystem::GetInstance()->RegisterCollider(position, currentSprite.GetScale(), this, EntityLayers::GetEntityLayer<BaseEnemy>(), true);
}

void Destroyer::Render(Renderer* const renderer)
{
	renderer->Render(position, currentSprite);
	const float healthBarHeight = 0.15f;
	//TODO: Error handle xScale == 0
	renderer->RenderQuad(position, FG::Vector2D(healthBarWidth, healthBarHeight), Color(0.3f, 0.3f, 0.3f, 1.0f), Color(0.3f, 0.3f, 0.3f, 1.0f));
	renderer->RenderQuad(position, FG::Vector2D(healthBarStepWidth * health, healthBarHeight), Color(1.0f, 0.3f, 0.3f, 1.0f), Color(1.0f, 0.3f, 0.3f, 1.0f));
}

void Destroyer::OnCollision(FG::Entity* other)
{
	if (usingLight && other->layer == EntityLayers::GetEntityLayer<DarkBullet>())
	{
		health--;
	}
	else if (!usingLight && other->layer == EntityLayers::GetEntityLayer<LightBullet>())
	{
		health--;
	}

}

void Destroyer::Shoot(FG::EntityManager* instance, FG::Vector2D startPos,float baseAngle, float angleOffset)
{
	if (usingLight)
	{
		instance->CreateEntity<LightBullet>(startPos,
			FG::Vector2D(
				std::clamp(std::cos(angleOffset + baseAngle), -1.0f, 1.0f),
				std::clamp(std::sin(angleOffset + baseAngle), -1.0f, 1.0f)),
			projectileSpeed, EntityLayers::GetEntityMask<Player>(), baseAngle + angleOffset, 1.0f);
	}
	else if (!usingLight)
	{
		instance->CreateEntity<DarkBullet>(startPos,
			FG::Vector2D(
				std::clamp(std::cos(angleOffset + baseAngle), -1.0f, 1.0f),
				std::clamp(std::sin(angleOffset + baseAngle), -1.0f, 1.0f)),
			projectileSpeed, EntityLayers::GetEntityMask<Player>(), baseAngle + angleOffset, 1.0f);
	}

}


