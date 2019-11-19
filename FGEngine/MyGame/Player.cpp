#include "Player.h"

#include <InputManager.h>
#include <Camera.h>

#include <SDL_render.h>
#include "CollisionSystem.h"
#include "Window.h"
#include "Bullet.h"
#include "EntityManager.h"
#include "BaseEnemy.h"


Player::Player(FG::InputManager* inputManager, FG::Sprite sprite ) :
	inputManager(inputManager), sprite(sprite)
{	
	collidesWith = EntityLayers::GetEntityMask<DarkBullet, LightBullet>();
}

void Player::Init()
{
	playerState = PLAYER_START_STATE;
	health = PLAYER_HEALTH;
	shootTimer = BasicTimer(PLAYER_SHOOT_TIMER);
	movementSpeed = PLAYER_MOVEMENTSPEED;
}

void Player::Start(FG::Vector2D startPos)
{
	FG::Entity::Start();
	Init();
	position = startPos;
}

void Player::Update(float deltaTime)
{
	MovePlayer(deltaTime);
	if (inputManager->IsKeyPressed(SDL_SCANCODE_Q) || inputManager->IsKeyPressed(SDL_SCANCODE_E))
	{
		SwapMode();
	}
	shootTimer.Update(deltaTime);
	if (inputManager->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		Shoot(deltaTime);
	}

	auto it = CollisionSystem::GetInstance();
	it->RegisterCollider(position, sprite.GetScale(), this, layer, true);
}

void Player::Render(Renderer* const camera)
{
	camera->Render(position, sprite);

	camera->RenderQuad(FG::Vector2D(0, 0), FG::Vector2D(PLAYER_HEALTH, 0.5f), Color(0.3f, 0.3f, 0.3f, 1.0f), Color(0.3f, 0.3f, 0.3f, 1.0f));
	camera->RenderQuad(FG::Vector2D(0, 0), FG::Vector2D(0.3f + (1 * health), 0.5f), Color(1.0f, 0.3f, 0.3f, 1.0f), Color(1.0f, 0.3f, 0.3f, 1.0f));
}

void Player::Shoot(float deltaTime)
{
	if (shootTimer.IsReady())
	{
		if (playerState == PLAYER_LIGHT_STATE)
		{
			SingleLightWeapon::Shoot(position, PLAYER_SHOOT_DIR, EntityLayers::GetEntityMask<BaseEnemy>());
		}
		else if (playerState == PLAYER_DARK_STATE)
		{
			SingleDarkWeapon::Shoot(position, PLAYER_SHOOT_DIR, EntityLayers::GetEntityMask<BaseEnemy>());
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
		//else, get power
	}
	else if (other->layer == EntityLayers::GetEntityLayer<DarkBullet>())
	{
		if (playerState == PLAYER_LIGHT_STATE)
		{
			health--;
		}
		//else, get power
	}
}

void Player::SwapMode()
{
	if (playerState == PLAYER_LIGHT_STATE)
	{
		playerState = PLAYER_DARK_STATE;
	}

	else if(playerState == PLAYER_DARK_STATE)
	{
		playerState = PLAYER_LIGHT_STATE;
	}
}

void Player::MovePlayer(float deltaTime)
{
	FG::Vector2D movement;
	if (inputManager->IsKeyDown(SDL_SCANCODE_A))
	{
		movement.x = -1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_D))
	{
		movement.x = 1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_W))
	{
		movement.y = -1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_S))
	{
		movement.y = 1.0f;
	}

	position += movement * movementSpeed * deltaTime;
}