#include "Player.h"

#include <InputManager.h>
#include <Camera.h>

#include <SDL_render.h>
#include "CollisionSystem.h"
#include "Window.h"
#include "Obstacle.h"
#include "BulletManager.h"

Player::Player()
	: bm(new BulletManager(BaseBullet(), 1000, FG::Sprite())), lightBulletManager(new BulletManager(BaseBullet(), 5000, FG::Sprite()))
{
	this->sprite.spriteIndex = 0;
	this->sprite.textureIndex = 0;
	this->sprite.SetScale(FG::Vector2D(1.0f, 1.0f));

}

Player::Player(FG::InputManager* inputManager, FG::Sprite sprite ) :
	inputManager(inputManager), bm(new BulletManager(BulletManager(BaseBullet(), 10000, sprite))), sprite(sprite), lightBulletManager(new BulletManager(LightBullet(), 10000, sprite))
{
	this->sprite.SetScale({ 1.0f, 1.0f });
	collidesWith = EntityLayers::GetEntityMask<Obstacle>();
	layer = EntityLayers::GetEntityLayer<Player>();
}

void Player::Update(float deltaTime)
{
	MovePlayer(deltaTime);
	Shoot(deltaTime);
	
	bm->Update(deltaTime);
	lightBulletManager->Update(deltaTime);

	auto it = CollisionSystem::GetInstance();

	it->RegisterCollider(position, sprite.GetScale(), this, true);
}

void Player::Render(Renderer* const camera)
{
	camera->Render(position, sprite);
	camera->RenderQuad(position, sprite.GetScale(), Color(), Color());
	bm->Render(camera);
	lightBulletManager->Render(camera);


}

void Player::Shoot(float deltaTime)
{
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
			lightBulletManager->Shoot((position + FG::Vector2D(1, 0)), { 1,0 });
		}
	}
	else
	{
		if (inputManager->IsKeyDown(SDL_SCANCODE_SPACE))
		{
			bm->Shoot((position + FG::Vector2D(1, 0)), { 1,0 });
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