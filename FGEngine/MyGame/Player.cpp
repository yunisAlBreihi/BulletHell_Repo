#include "Player.h"

#include <InputManager.h>
#include <Camera.h>

#include <SDL_render.h>
#include "CollisionSystem.h"
#include "Window.h"
#include "Obstacle.h"
#include "BulletManager.h"

Player::Player(FG::InputManager* inputManager, FG::Sprite sprite ) :
	inputManager(inputManager), bm(BulletManager(LightBullet(), 5000, sprite)), sprite(sprite)
{
	collidesWith = EntityLayers::GetEntityMask<Obstacle>();
	layer = EntityLayers::GetEntityLayer<Player>();
}

void Player::Update(float deltaTime)
{
	MovePlayer(deltaTime);
	Shoot(deltaTime);
	bm.Update(deltaTime);
	auto it = CollisionSystem::GetInstance();

	it->RegisterCollider(position, sprite.size, this, true);
}

void Player::Render(Renderer* const camera)
{
	//sprite.SetIndex(sprite.spriteIndex + 1);
	//if (sprite.spriteIndex >= 64)
	//{
	//	sprite.spriteIndex = 0;
	//}
	camera->Render(position, sprite);

	bm.Render(camera);

	//SDL_Color oldDrawColor;
	//SDL_GetRenderDrawColor(camera->GetInternalRenderer(),
	//	&oldDrawColor.r, &oldDrawColor.g, &oldDrawColor.b, &oldDrawColor.a);

	//sprite->Render(camera, position);
	//DrawBoundingBox();
	//isColliding = false;

	//SDL_SetRenderDrawColor(camera->GetInternalRenderer(),
	//	oldDrawColor.r, oldDrawColor.g, oldDrawColor.b, oldDrawColor.a);
}

void Player::Shoot(float deltaTime)
{
	if (inputManager->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		bm.Shoot((position + FG::Vector2D(1, 0)), { 1,0 });
	}
}

SDL_Rect Player::GetColliderRectangle()
{
	//FG::Vector2D finalPosition = position - camera->position;
	//return { (int)finalPosition.x, (int)finalPosition.y,
	//(int)sprite->size.x, (int)sprite->size.y };
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

void Player::DrawBoundingBox()
{
	//SDL_Color color = notCollidingColor;
	//if (isColliding)
	//{
	//	color = CollidingColor;
	//}

	//SDL_Rect finalRect = GetColliderRectangle();
	//SDL_SetRenderDrawColor(camera->GetInternalRenderer(),
	//	color.r, color.g, color.b, color.a);

	//SDL_RenderDrawRect(camera->GetInternalRenderer(), &finalRect);
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