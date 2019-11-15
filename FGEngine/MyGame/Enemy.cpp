#include "Enemy.h"
#include "Camera.h"
#include "Sprite.h"
#include <SDL_render.h>

Enemy::Enemy(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites)
	: sprite(sprite), position(position), bullets(BaseBullet(), 30, bulletsSprites)
{

}

void Enemy::Update(float deltaTime)
{
	accu += deltaTime;
	if (accu >= timer)
	{
		bullets.Shoot(position + FG::Vector2D(0, 100), FG::Vector2D(0, 10));
		accu = 0;
	}
	bullets.Update(deltaTime);
}

void Enemy::Render(Renderer* const camera)
{
	//sprite.size = { 0.5f, 0.5f };
	camera->Render(position, sprite);
	/*RenderBullets(camera);

	SDL_Color oldDrawColor;
	SDL_GetRenderDrawColor(camera->GetInternalRenderer(),
		&oldDrawColor.r, &oldDrawColor.g, &oldDrawColor.b, &oldDrawColor.a);

	sprite->Render(camera, position);
	DrawBoundingBox();
	isColliding = false;

	SDL_SetRenderDrawColor(camera->GetInternalRenderer(),
		oldDrawColor.r, oldDrawColor.g, oldDrawColor.b, oldDrawColor.a);*/
}

void Enemy::TestCollision(Entity* other)
{
	bullets.TestCollision(other);
}

void Enemy::DrawBoundingBox()
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

void Enemy::RenderBullets(Renderer *const renderer)
{
	bullets.Render(renderer);
}

SDL_Rect Enemy::GetColliderRectangle()
{
	//FG::Vector2D finalPosition = position - camera->position;
	//return { (int)finalPosition.x, (int)finalPosition.y,
	//(int)sprite.size.x, (int)sprite.size.y };
	return { 0,0,0,0 };
}
