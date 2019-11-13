#pragma once
#include <vector>
#include "Vector2D.h"
#include "Entity.h"
#include "Intevals.h"
#include "Sprite.h"
#include "Camera.h"
#include <iostream>

namespace FG
{
	class Window;
	class InputManager;
}

class BulletManager;

class BaseBullet : public FG::Entity
{
public:
	BaseBullet();
	void Init(BulletManager* manager, int index, float speed);
	bool active = false;
	FG::Vector2D position;
	FG::Vector2D dir;
	float speed;

	FG::Sprite sprite;
	BulletManager* bulletManager;
	int index;

	virtual void OnCollision(Entity* other) override;
	void Update(float deltaTime);
};

class LightBullet : public BaseBullet
{
public:
	LightBullet();
	void Update(float deltaTime);
	virtual void OnCollision(Entity* other) override;
};


class BulletManager : public FG::Entity
{
public:
	template <class T>
	BulletManager(T obj, size_t count, FG::Sprite sprite);
	void Update(float deltaTime);
	void Shoot(const FG::Vector2D& position, const FG::Vector2D& direction);
	void DisableBullet(int index);
	void Render(Renderer* camera) override;

private:
	IntervalSet freeIndices;
	std::vector<BaseBullet*> bullets;
	
};

template <class T>
inline BulletManager::BulletManager(T obj, size_t count, FG::Sprite sprite)
{
	(void)static_cast<BaseBullet*>((T*)0);
	freeIndices = IntervalSet(0, count);
	for (int i = 0; i < count; i++)
	{
		bullets.emplace_back(new T());
		bullets[i]->Init(this, i, 10.0f);

		freeIndices.Use(i);
		bullets[i]->position.x = 0;
		bullets[i]->position.y = 0;
		bullets[i]->sprite = sprite;
	}
}
