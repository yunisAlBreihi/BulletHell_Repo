#include "Player.h"

#include <InputManager.h>
#include <Camera.h>

#include <SDL_render.h>
#include "CollisionSystem.h"
#include "Window.h"
#include "Obstacle.h"
#include "BulletManager.h"

Player::Player(FG::InputManager* inputManager, FG::Sprite sprite ) :
	inputManager(inputManager), bm(BulletManager(BaseBullet(), 500, sprite)), sprite(sprite), lightBulletManager(BulletManager(LightBullet(), 500, sprite))
{
	this->sprite.size = { 2.5f, 2.5f };
	collidesWith = EntityLayers::GetEntityMask<Obstacle>();
	layer = EntityLayers::GetEntityLayer<Player>();
}

void Player::Update(float deltaTime)
{
	MovePlayer(deltaTime);
	Shoot(deltaTime);
	
	bm.Update(deltaTime);
	lightBulletManager.Update(deltaTime);

	auto it = CollisionSystem::GetInstance();
	it->RegisterCollider(position, sprite.size, this, true);
}

void Player::Render(Renderer* const camera)
{
	camera->Render(position, sprite);
	bm.Render(camera);
	lightBulletManager.Render(camera);
}

void Player::Shoot(float deltaTime)
{
	if (inputManager->IsKeyDown(SDL_SCANCODE_Q))
	{
		usingLight = false;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_E))
	{
		usingLight = true;
	}
	if (usingLight)
	{
		if (inputManager->IsKeyDown(SDL_SCANCODE_SPACE))
		{
			lightBulletManager.Shoot((position + FG::Vector2D(1, 0)), { 1,0 });
		}
	}
	else
	{
		if (inputManager->IsKeyDown(SDL_SCANCODE_SPACE))
		{
			bm.Shoot((position + FG::Vector2D(1, 0)), { 1,0 });
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