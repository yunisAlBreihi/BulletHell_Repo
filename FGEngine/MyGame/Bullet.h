#pragma once
#include <vector>
#include "Vector2D.h"
#include "Entity.h"
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

	void Update(float deltaTime) override;
	void Render(Renderer* const renderer) override;

	FG::Vector2D position;
	FG::Vector2D dir;
	float speed;
	FG::Sprite sprite;
};

class LightBullet : public BaseBullet
{
public:
	LightBullet(FG::Sprite sprite);
	void Update(float deltaTime) override;
	void Start(const FG::Vector2D position, const FG::Vector2D direction, float speed, uint64_t collidesWith);
	void Start(const FG::Vector2D position, const FG::Vector2D direction, float speed, uint64_t collidesWith, float rotation, float rotationRate);
	virtual void OnCollision(FG::Entity* other) override;

	float rotation;
	float startRotation;

	float rotationRate;
	bool rotatedOneTime;
	bool rotatingBullet;
};

class DarkBullet : public BaseBullet
{
public:
	DarkBullet(FG::Sprite sprite);
	void Update(float deltaTime);
	void Start(const FG::Vector2D position, const FG::Vector2D direction, float speed, uint64_t collidesWith);
	void Start(const FG::Vector2D position, const FG::Vector2D direction, float speed, uint64_t collidesWith, float rotation , float rotationRate);
	virtual void OnCollision(FG::Entity* other) override;


	float rotation;
	float startRotation;

	float rotationRate;
	bool rotatedOneTime;
	bool rotatingBullet;
};