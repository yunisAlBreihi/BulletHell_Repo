#include "PlayerWeapon.h"
#include "EntityManager.h"
#include "Bullet.h"

void SingleLightWeapon::Shoot(const FG::Vector2D& startPos, const FG::Vector2D& dir, const uint64_t collidesWith)
{
	FG::EntityManager::Instance()->CreateEntity<LightBullet>(startPos, dir, SINGLE_LIGHT_SPEED, collidesWith);
}

void SingleDarkWeapon::Shoot(const FG::Vector2D& startPos, const FG::Vector2D& dir, const uint64_t collidesWith)
{
	FG::EntityManager::Instance()->CreateEntity<DarkBullet>(startPos, dir, SINGLE_DARK_SPEED, collidesWith);
}

void BurstDarkWeapon::Shoot(const FG::Vector2D& startPos, const FG::Vector2D& dir, const uint64_t collidesWith)
{
	FG::EntityManager::Instance()->CreateEntity<DarkBullet>(startPos, FG::Vector2D(dir.x, 0.3f), SINGLE_DARK_SPEED, collidesWith);
	FG::EntityManager::Instance()->CreateEntity<DarkBullet>(startPos, FG::Vector2D(dir.x, 0.15f), SINGLE_DARK_SPEED, collidesWith);
	FG::EntityManager::Instance()->CreateEntity<DarkBullet>(startPos, dir, SINGLE_DARK_SPEED, collidesWith);
	FG::EntityManager::Instance()->CreateEntity<DarkBullet>(startPos, FG::Vector2D(dir.x, -0.15f), SINGLE_DARK_SPEED, collidesWith);
	FG::EntityManager::Instance()->CreateEntity<DarkBullet>(startPos, FG::Vector2D(dir.x, -0.3f), SINGLE_DARK_SPEED, collidesWith);
}

void BurstLightWeapon::Shoot(const FG::Vector2D& startPos, const FG::Vector2D& dir, const uint64_t collidesWith)
{
	FG::EntityManager::Instance()->CreateEntity<LightBullet>(startPos, FG::Vector2D(dir.x, 0.3f), SINGLE_DARK_SPEED, collidesWith);
	FG::EntityManager::Instance()->CreateEntity<LightBullet>(startPos, FG::Vector2D(dir.x, 0.15f), SINGLE_DARK_SPEED, collidesWith);
	FG::EntityManager::Instance()->CreateEntity<LightBullet>(startPos, dir, SINGLE_DARK_SPEED, collidesWith);
	FG::EntityManager::Instance()->CreateEntity<LightBullet>(startPos, FG::Vector2D(dir.x, -0.15f), SINGLE_DARK_SPEED, collidesWith);
	FG::EntityManager::Instance()->CreateEntity<LightBullet>(startPos, FG::Vector2D(dir.x, -0.3f), SINGLE_DARK_SPEED, collidesWith);
}

void LazerLightWeapon::Shoot(const FG::Vector2D& startPos, const FG::Vector2D& dir, const uint64_t collidesWith)
{
}

void LazerDarkWeapon::Shoot(const FG::Vector2D& startPos, const FG::Vector2D& dir, const uint64_t collidesWith)
{
}
