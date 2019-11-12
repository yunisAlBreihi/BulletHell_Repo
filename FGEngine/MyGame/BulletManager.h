#pragma once
#include <vector>
#include "Vector2D.h"
#include "Entity.h"
#include "Intevals.h"
namespace FG
{
	class Window;
	class InputManager;
	class Camera;
	class Sprite;
}

class BulletManager : public FG::Entity
{
	class _Bullet : public FG::Entity
	{
	public:
		bool active = false;
		FG::Vector2D position;
		FG::Vector2D dir;
		FG::Sprite* sprite;
		BulletManager* bulletManager;
		int index;

		virtual void OnCollision(Entity* other) override;
	};

public:
	BulletManager(size_t count, FG::Sprite* sprite);

	void Update(float deltaTime);
	void Shoot(const FG::Vector2D& position, const FG::Vector2D& direction);
	void DisableBullet(int index);

	void Render(FG::Camera* camera);

private:
	IntervalSet freeIndices;
	std::vector<_Bullet> bullets;
};