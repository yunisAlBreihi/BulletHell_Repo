#include "Enemy.h"
#include "Camera.h"
#include "Sprite.h"
#include <SDL_render.h>
#include "CollisionSystem.h"
Enemy::Enemy(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites)
	: sprite(sprite), position(position), bullets(new BulletManager(BaseBullet(), 30, bulletsSprites))
{
	layer = EntityLayers::GetEntityLayer<Enemy>();
	collidesWith = EntityLayers::GetEntityMask<BaseBullet>();
}

void Enemy::Start()
{
	Entity::Start();
}

void Enemy::Start(FG::Vector2D position, FG::Sprite sprite)
{
	Entity::Start();
	this->position = position;
	this->sprite = sprite;
	//this->bullets->sprite = bulletsSprite;
}

void Enemy::Update(float deltaTime)
{
	accu += deltaTime;
	if (accu >= timer)
	{
		bullets->Shoot(position + FG::Vector2D(0, 100), FG::Vector2D(0, 10));
		accu = 0;
	}
	bullets->Update(deltaTime);
	auto it = CollisionSystem::GetInstance();
	it->RegisterCollider(position, sprite.GetScale(), this, true);
}

void Enemy::Render(Renderer* const camera)
{
	camera->RenderQuad(position, sprite.GetScale(), Color(), Color());
	camera->Render(position, sprite);
}

void Enemy::TestCollision(Entity* other)
{
	bullets->TestCollision(other);
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
	bullets->Render(renderer);
}

SDL_Rect Enemy::GetColliderRectangle()
{
	//FG::Vector2D finalPosition = position - camera->position;
	//return { (int)finalPosition.x, (int)finalPosition.y,
	//(int)sprite.size.x, (int)sprite.size.y };
	return { 0,0,0,0 };
}
