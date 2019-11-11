#include "Obstacle.h"

#include<Sprite.h>
#include <Camera.h>
#include <SDL_render.h>

void Obstacle::Render(FG::Camera* const camera)
{
	SDL_Color oldDrawColor;
	SDL_GetRenderDrawColor(camera->GetInternalRenderer(),
		&oldDrawColor.r, &oldDrawColor.g, &oldDrawColor.b, &oldDrawColor.a);

	sprite->Render(camera, position);
	DrawBoundingBox();
	isColliding = false;

	SDL_SetRenderDrawColor(camera->GetInternalRenderer(),
		oldDrawColor.r, oldDrawColor.g, oldDrawColor.b, oldDrawColor.a);
}

SDL_Rect Obstacle::GetColliderRectangle()
{
	FG::Vector2D finalPosition = position - camera->position;
	return { (int)finalPosition.x, (int)finalPosition.y,
	(int)sprite->size.x, (int)sprite->size.y };
}

void Obstacle::OnCollision(FG::Entity* other)
{
	isColliding = true;
}

void Obstacle::DrawBoundingBox()
{
	SDL_Color color = notCollidingColor;
	if (isColliding)
	{
		color = CollidingColor;
	}

	SDL_Rect finalRect = GetColliderRectangle();
	SDL_SetRenderDrawColor(camera->GetInternalRenderer(),
		color.r, color.g, color.b, color.a);

	SDL_RenderDrawRect(camera->GetInternalRenderer(), &finalRect);
}
