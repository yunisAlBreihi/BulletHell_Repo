#include "Enemy01.h"
#include "Camera.h"
#include "Sprite.h"
#include <SDL_render.h>
#include <cmath>

Enemy01::Enemy01(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites)
	: sprite(sprite), position(position), bullets(BaseBullet(), 150, bulletsSprites)
{ 

}

void Enemy01::Update(float deltaTime)
{
	centerPos.x -= speed * deltaTime;

	angle += orbitSpeed * deltaTime;
	position.x = centerPos.x + orbitRadius * cos(angle);
	position.y = centerPos.y*1.75f + orbitRadius * sin(angle);

	if (centerPos.x < -5.5f)
	{
		centerPos.x = 5.5f;
	}

	bulletSpread += 1.0f* deltaTime *bulletDirection;

	if (bulletSpread <-0.85f || bulletSpread > 0.85f)
	{
		bulletDirection *= -1;
	}

	accu += deltaTime;
	if (accu >= timer)
	{
		bullets.Shoot((position + FG::Vector2D(-1, 0)), { -0.5f, bulletSpread });
		accu = 0;
	}
	bullets.Update(deltaTime);
}

void Enemy01::Render(Renderer* const camera)
{
	camera->Render(position, sprite);
	bullets.Render(camera);
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

void Enemy01::TestCollision(Entity* other)
{
	bullets.TestCollision(other);
}

void Enemy01::DrawBoundingBox()
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

void Enemy01::RenderBullets(Renderer* const renderer)
{
	bullets.Render(renderer);
}

SDL_Rect Enemy01::GetColliderRectangle()
{
	//FG::Vector2D finalPosition = position - camera->position;
	//return { (int)finalPosition.x, (int)finalPosition.y,
	//(int)sprite.size.x, (int)sprite.size.y };
	return { 0,0,0,0 };
}
