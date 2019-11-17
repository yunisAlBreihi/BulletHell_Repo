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


class BaseBullet : public FG::Entity
{
public:
	BaseBullet();
	
	void Start(const FG::Vector2D position, const FG::Vector2D direction, float speed, uint64_t collidesWith);

	FG::Vector2D position;
	FG::Vector2D dir;
	float speed;

	FG::Sprite sprite;

	virtual void OnCollision(Entity* other) override;
	void Update(float deltaTime);
	void Render(Renderer* const renderer) override;
};

class LightBullet : public BaseBullet
{
public:
	LightBullet();
	void Update(float deltaTime);
	void Start(const FG::Vector2D position, const FG::Vector2D direction, float speed, uint64_t collidesWith);

	virtual void OnCollision(Entity* other) override;
};