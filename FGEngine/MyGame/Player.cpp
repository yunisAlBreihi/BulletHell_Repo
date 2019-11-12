#include "Player.h"

#include <InputManager.h>
#include <Camera.h>

#include <SDL_render.h>
#include "CollisionSystem.h"
Player::Player(FG::InputManager* inputManager, FG::Sprite sprite ) :
	inputManager(inputManager), bm(BulletManager(5, sprite)), sprite(sprite)
{
}

void Player::Update(float deltaTime)
{
	MovePlayer(deltaTime);
	MoveCamera(deltaTime);
	Shoot(deltaTime);
	auto it = CollisionSystem::GetInstance();
	it->RegisterCollider(position, sprite.size, this, true);
}

void Player::Render(Renderer* const camera)
{
	sprite.size = { 0.5f, 0.5f };
	camera->Render(position, sprite);
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
		if (inputManager->IsKeyDown(SDL_SCANCODE_F))
		{
			bm.Shoot((position + FG::Vector2D(200, 0)), { 1,0 });
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
	isColliding = true;
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

void Player::MoveCamera(float deltaTime)
{
	FG::Vector2D movement;
	if (inputManager->IsKeyDown(SDL_SCANCODE_LEFT))
	{
		movement.x = -1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		movement.x = 1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_UP))
	{
		movement.y = -1.0f;
	}

	if (inputManager->IsKeyDown(SDL_SCANCODE_DOWN))
	{
		movement.y = 1.0f;
	}

	//camera->position += movement * speed * deltaTime;
}
