#include "Obstacle.h"

#include<Sprite.h>
#include <Camera.h>
#include <SDL_render.h>
#include "CollisionSystem.h"
#include "BulletManager.h"
#include "Player.h"

void Obstacle::Render(Renderer* const camera)
{
	camera->Render(position, sprite);
	/*SDL_Color oldDrawColor;
	SDL_GetRenderDrawColor(camera->GetInternalRenderer(),
		&oldDrawColor.r, &oldDrawColor.g, &oldDrawColor.b, &oldDrawColor.a);

	sprite->Render(camera, position);
	DrawBoundingBox();
	isColliding = false;

	SDL_SetRenderDrawColor(camera->GetInternalRenderer(),
		oldDrawColor.r, oldDrawColor.g, oldDrawColor.b, oldDrawColor.a);*/
}

void Obstacle::Update(float deltaTime)
{
	auto it = CollisionSystem::GetInstance();
	it->RegisterCollider(position, sprite.size, this, true, it->GetObjectLayer<Obstacle>(), it->GetCollisionMask<_Bullet, Player>());
}

SDL_Rect Obstacle::GetColliderRectangle()
{
	/*FG::Vector2D finalPosition = position - camera->position;
	return { (int)finalPosition.x, (int)finalPosition.y,
	(int)sprite->size.x, (int)sprite->size.y };*/
	return { 0,0,0,0 };
}

void Obstacle::OnCollision(FG::Entity* other)
{
	isColliding = true;
}

void Obstacle::DrawBoundingBox()
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
