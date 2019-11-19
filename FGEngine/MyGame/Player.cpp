#include "Player.h"

#include <InputManager.h>
#include <Camera.h>

#include <SDL_render.h>
#include "CollisionSystem.h"
#include "Window.h"
#include "Obstacle.h"
#include "Bullet.h"
#include "EntityManager.h"
#include "Enemy.h"

Player::Player()
{
	this->sprite.spriteIndex = 0;
	this->sprite.textureIndex = 0;
	this->sprite.SetScale(FG::Vector2D(1.0f, 1.0f));
}

Player::Player(FG::InputManager* inputManager, FG::Sprite sprite ) :
	inputManager(inputManager), sprite(sprite)
{
	this->sprite.SetScale({ 1.0f, 1.0f });
	collidesWith = EntityLayers::GetEntityMask<Obstacle, BaseBullet>();
	layer = EntityLayers::GetEntityLayer<Player>();
}

void Player::Update(float deltaTime)
{
	MovePlayer(deltaTime);
	Shoot(deltaTime);

	auto it = CollisionSystem::GetInstance();
	it->RegisterCollider(position, sprite.GetScale(), this, true);
}

void Player::Render(Renderer* const camera)
{
	camera->Render(position, sprite);
	camera->RenderQuad(position, sprite.GetScale(), Color(), Color());
}

void Player::Shoot(float deltaTime)
{
	accu += deltaTime;
	if (inputManager->IsKeyPressed(SDL_SCANCODE_Q))
	{
		usingLight = false;
	}

	if (inputManager->IsKeyPressed(SDL_SCANCODE_E))
	{
		usingLight = true;
	}

	if (usingLight)
	{
		if (inputManager->IsKeyDown(SDL_SCANCODE_SPACE))
		{
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<LightBullet>(position, FG::Vector2D(1, 0), 10.0f, EntityLayers::GetEntityMask<Enemy>());
				accu = 0;
			}
		}
	}
	else
	{
		if (inputManager->IsKeyDown(SDL_SCANCODE_SPACE))
		{
			if (accu >= timer)
			{
				FG::EntityManager::Instance()->CreateEntity<BaseBullet>(position, FG::Vector2D(1, 0), 10.0f, EntityLayers::GetEntityMask<Enemy>());
				accu = 0;
			}
		}
	}
}

SDL_Rect Player::GetColliderRectangle()
{
	return { 0,0,0,0 };
}

void Player::OnCollision(FG::Entity* other)
{
	auto it = CollisionSystem::GetInstance();
	if (other->layer == EntityLayers::GetEntityLayer<Obstacle>())
	{
		isColliding = true;
		std::cout << "colliding!" << std::endl;
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

	position += movement * speed * deltaTime;
}