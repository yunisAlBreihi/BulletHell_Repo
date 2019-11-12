#include "Projectile.h"

#include <Camera.h>
#include <Sprite.h>
#include <SDL_render.h>

Projectile::Projectile(FG::Camera* camera) : camera(camera)
{

}

void Projectile::Update(float deltaTime)
{
	Move(deltaTime);
}

void Projectile::Render(FG::Camera* const camera)
{
	SDL_Color oldDrawColor;
	SDL_GetRenderDrawColor(camera->GetInternalRenderer(),
		&oldDrawColor.r, &oldDrawColor.g, &oldDrawColor.b, &oldDrawColor.a);

	sprite->Render(camera, position, true);
	DrawBoundingBox();
	isColliding = false;

	SDL_SetRenderDrawColor(camera->GetInternalRenderer(),
		oldDrawColor.r, oldDrawColor.g, oldDrawColor.b, oldDrawColor.a);
}

SDL_Rect Projectile::GetColliderRectangle()
{
	FG::Vector2D finalPosition = position - camera->position;

	return { (int)finalPosition.x, (int)finalPosition.y,
	(int)sprite->size.x, (int)sprite->size.y };
}

void Projectile::OnCollision(FG::Entity* other)
{
	isColliding = true;
}

void Projectile::SetPosition(FG::Vector2D pos)
{
	position = pos;
}

Projectile::~Projectile()
{
	
}

void Projectile::DrawBoundingBox()
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

void Projectile::Move(float deltaTime)
{
	FG::Vector2D movement;

	movement.y = -1.0f;

	position += movement * speed * deltaTime;
}
