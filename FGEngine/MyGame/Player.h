#pragma once

#include <Entity.h>
#include <Vector2D.h>
#include "Bullet.h"
#include "Sprite.h"
namespace FG
{
	class Window;
	class InputManager;
	class Sprite;
}

class Player : public FG::Entity
{
public:
	float speed = 5.0f;
	FG::Sprite sprite;
	Player();
	Player(FG::InputManager* inputManager, FG::Sprite sprite);
	~Player() {}
	void Update(float deltaTime) override;
	void Render(Renderer* const renderer) override;
	void Shoot(float deltaTime);
	SDL_Rect GetColliderRectangle();
	void OnCollision(FG::Entity* other) override;
	FG::Vector2D position;
private:
	FG::InputManager* inputManager = nullptr;


	float timer = 0.05f;
	float accu = 0;

	bool isColliding = false;
	SDL_Color notCollidingColor = { 0, 255, 0, 255 };
	SDL_Color CollidingColor = { 255, 0, 0, 255 };

	bool usingLight = false;
	void MovePlayer(float deltaTime);
};
