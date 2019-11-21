#include "Player.h"

#include <InputManager.h>
#include <Camera.h>

#include <SDL_render.h>
#include "CollisionSystem.h"
#include "Window.h"
#include "Bullet.h"
#include "EntityManager.h"
#include "BaseEnemy.h"

Player::Player(FG::InputManager* inputManager, FG::Sprite lightSprite, FG::Sprite darkSprite ) :
	inputManager(inputManager), lightSprite(lightSprite), darkSprite(darkSprite)
{	
	animationTimer = BasicTimer(0.15f);
	currentSprite = lightSprite;
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
	it->RegisterCollider(position + (darkSprite.GetScale() * 0.5f), FG::Vector2D(0.05f, 0.05f), this, layer, true);
}

void Player::Render(Renderer* const camera)
{
	camera->Render(position, currentSprite);
	camera->RenderQuad(position + (darkSprite.GetScale() * 0.5f), FG::Vector2D(0.05f, 0.05f), Color(0), Color(1.0f, 0.0f, 0.5f, 1.0f));

	//health bar
	camera->RenderQuad(FG::Vector2D(0, 0), FG::Vector2D(PLAYER_HEALTH, 0.5f), Color(0.3f, 0.3f, 0.3f, 1.0f), Color(0.3f, 0.3f, 0.3f, 1.0f));
	camera->RenderQuad(FG::Vector2D(0, 0), FG::Vector2D(0.3f + (1 * health), 0.5f), Color(1.0f, 0.3f, 0.3f, 1.0f), Color(1.0f, 0.3f, 0.3f, 1.0f));
}

void Player::Shoot(float deltaTime)
{
	if (shootTimer.IsReady())
	{
		if (playerState == PLAYER_LIGHT_STATE)
		{
			BurstLightWeapon::Shoot(position, PLAYER_SHOOT_DIR, EntityLayers::GetEntityMask<BaseEnemy>());
		}
		else if (playerState == PLAYER_DARK_STATE)
		{
			BurstDarkWeapon::Shoot(position, PLAYER_SHOOT_DIR, EntityLayers::GetEntityMask<BaseEnemy>());
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
		currentSprite.textureIndex = darkSprite.textureIndex;
	}

	else if(playerState == PLAYER_DARK_STATE)
	{
		playerState = PLAYER_LIGHT_STATE;
		currentSprite.textureIndex = lightSprite.textureIndex;
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

	position.x = std::clamp(position.x, 0.0f, 20.0f - darkSprite.GetScale().x);
	position.y = std::clamp(position.y, 0.0f, (20.0f * FG::Window::aspectRatio) - darkSprite.GetScale().y);
}