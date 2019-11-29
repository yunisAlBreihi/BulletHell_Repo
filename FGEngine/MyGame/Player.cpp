#include "Player.h"

#include <InputManager.h>
#include <Camera.h>

#include <SDL_render.h>
#include "CollisionSystem.h"
#include "Window.h"
#include "Bullet.h"
#include "EntityManager.h"
#include "BaseEnemy.h"
#include "WeaponPickup.h"

Player::Player(FG::Sprite lightSprite, FG::Sprite darkSprite) :
	lightSprite(lightSprite), darkSprite(darkSprite)
{	
	animationTimer = BasicTimer(0.15f);
	currentSprite = lightSprite;
	collidesWith = EntityLayers::GetEntityMask<DarkBullet, LightBullet, WeaponPickup>();
}

void Player::Init()
{
	playerState = PLAYER_START_STATE;
	health = PLAYER_HEALTH;
	shootTimer = BasicTimer(PLAYER_SHOOT_TIMER);
	movementSpeed = PLAYER_MOVEMENTSPEED;
}

void Player::Start(FG::Vector2D startPos, int index)
{
	this->index = index;
	Init();
	position = startPos;
	accumulateCharge = 0;
}

void Player::Update(float deltaTime)
{
	MovePlayer(deltaTime);
	animationTimer.Update(deltaTime);

	if (animationTimer.IsReady())
	{
		currentSprite.SetIndex(++currentSprite.spriteIndex);
		if (currentSprite.spriteIndex > 3)
		{
			currentSprite.spriteIndex = 0;
		}
		animationTimer.Use();
	}
	if (FG::InputManager::IsKeyPressed(SDL_SCANCODE_Q) || FG::InputManager::IsKeyPressed(SDL_SCANCODE_E) || FG::InputManager::GetButtonDown(index, SDL_CONTROLLER_BUTTON_Y))
	{
		SwapMode();
	}
	shootTimer.Update(deltaTime);
	if (FG::InputManager::IsKeyDown(SDL_SCANCODE_SPACE) || FG::InputManager::GetButton(index, SDL_CONTROLLER_BUTTON_A))
	{
		Shoot(deltaTime);
	}

	auto it = CollisionSystem::GetInstance();
	it->RegisterCollider(position + (darkSprite.GetScale() * 0.5f), FG::Vector2D(0.05f, 0.05f), this, layer, true);
}

void Player::Render(Renderer* const camera)
{
	camera->Render(position, currentSprite);
	camera->RenderQuad(position + (darkSprite.GetScale() * 0.5f), FG::Vector2D(0.05f, 0.05f), Color(0), Color(1.0f, 0.0f, 0.5f, 1.0f));
	camera->RenderQuad(FG::Vector2D(0, 0), FG::Vector2D(PLAYER_HEALTH, 0.5f), Color(0.3f, 0.3f, 0.3f, 1.0f), Color(0.3f, 0.3f, 0.3f, 1.0f));
	camera->RenderQuad(FG::Vector2D(0, 0), FG::Vector2D(0.3f + (1 * health), 0.5f), Color(1.0f, 0.3f, 0.3f, 1.0f), Color(1.0f, 0.3f, 0.3f, 1.0f));
}

void Player::Shoot(float deltaTime)
{
	if (shootTimer.IsReady())
	{
		if (playerState == PLAYER_LIGHT_STATE)
		{
			BurstLightWeapon::Shoot(position + FG::Vector2D(currentSprite.GetScale().x, currentSprite.GetScale().y * 0.25f), PLAYER_SHOOT_DIR, EntityLayers::GetEntityMask<BaseEnemy>());
		}
		else if (playerState == PLAYER_DARK_STATE)
		{
			BurstDarkWeapon::Shoot(position + FG::Vector2D(currentSprite.GetScale().x, currentSprite.GetScale().y * 0.25f), PLAYER_SHOOT_DIR, EntityLayers::GetEntityMask<BaseEnemy>());
		}
		shootTimer.Use();
	}
}

void Player::OnCollision(FG::Entity* other)
{
	if (other->layer == EntityLayers::GetEntityLayer<LightBullet>())
	{
		if (playerState == PLAYER_DARK_STATE)
		{
			health--;
		}
		else
		{
			accumulateCharge++;
			if (accumulateCharge > PLAYER_MAX_BULLET_ACCUMULATION)
			{
				accumulateCharge = PLAYER_MAX_BULLET_ACCUMULATION;
			}
		}
	}
	else if (other->layer == EntityLayers::GetEntityLayer<DarkBullet>())
	{
		if (playerState == PLAYER_LIGHT_STATE)
		{
			health--;
		}
		else
		{
			accumulateCharge++;
			if (accumulateCharge > PLAYER_MAX_BULLET_ACCUMULATION)
			{
				accumulateCharge = PLAYER_MAX_BULLET_ACCUMULATION;
			}
		}
	}
}

void Player::SwapMode()
{
	if (playerState == PLAYER_LIGHT_STATE)
	{
		playerState = PLAYER_DARK_STATE;
		currentSprite.textureIndex = darkSprite.textureIndex;

		float baseAngle = 0;
		for (int i = 0; i < accumulateCharge; i++)
		{
			float angleOffset = 2.0f * M_PI * (((float)i) / accumulateCharge);
			FG::EntityManager::Instance()->CreateEntity<LightBullet>(position,
				FG::Vector2D(
					std::clamp(std::cos(angleOffset + baseAngle), -1.0f, 1.0f),
					std::clamp(std::sin(angleOffset + baseAngle), -1.0f, 1.0f)),
				PLAYER_BULLET_SPEED, EntityLayers::GetEntityMask<BaseEnemy>(), baseAngle + angleOffset, 1.0f);
		}
		accumulateCharge = 0;
	}

	else if(playerState == PLAYER_DARK_STATE)
	{
		playerState = PLAYER_LIGHT_STATE;
		currentSprite.textureIndex = lightSprite.textureIndex;

		float baseAngle = 0;
		for (int i = 0; i < accumulateCharge; i++)
		{
			float angleOffset = 2.0f * M_PI * (((float)i) / accumulateCharge);
			FG::EntityManager::Instance()->CreateEntity<DarkBullet>(position,
				FG::Vector2D(
					std::clamp(std::cos(angleOffset + baseAngle), -1.0f, 1.0f),
					std::clamp(std::sin(angleOffset + baseAngle), -1.0f, 1.0f)),
				PLAYER_BULLET_SPEED, EntityLayers::GetEntityMask<BaseEnemy>(), baseAngle + angleOffset, 1.0f);
		}
		accumulateCharge = 0;
	}
}

void Player::MovePlayer(float deltaTime)
{
	float xAxis = FG::InputManager::GetGamepadAxis(index, SDL_CONTROLLER_AXIS_LEFTX);
	float yAxis = FG::InputManager::GetGamepadAxis(index, SDL_CONTROLLER_AXIS_LEFTY);

	FG::Vector2D movement;

	float deadZone = 5000;

	if (xAxis < deadZone && xAxis > -deadZone)
	{
		xAxis = 0;
	}
	if (yAxis < deadZone && yAxis > -deadZone)
	{
		yAxis = 0;
	}
	movement.x = xAxis * 0.000030517578125f;
	movement.y = yAxis * 0.000030517578125f;

	if (FG::InputManager::IsKeyDown(SDL_SCANCODE_A))
	{
		movement.x = -1.0f;
	}

	if (FG::InputManager::IsKeyDown(SDL_SCANCODE_D))
	{
		movement.x = 1.0f;
	}

	if (FG::InputManager::IsKeyDown(SDL_SCANCODE_W))
	{
		movement.y = -1.0f;
	}

	if (FG::InputManager::IsKeyDown(SDL_SCANCODE_S))
	{
		movement.y = 1.0f;
	}

	position += movement * movementSpeed * deltaTime;

	position.x = std::clamp(position.x, 0.0f, 20.0f - darkSprite.GetScale().x);
	position.y = std::clamp(position.y, 0.0f, (20.0f * FG::Window::aspectRatio) - darkSprite.GetScale().y);
}