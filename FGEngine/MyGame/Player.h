#pragma once

#include <Entity.h>
#include <Vector2D.h>
#include "BulletManager.h"
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
	BulletManager bm;
	BulletManager lightBulletManager;
	float speed = 5.0f;
	FG::Sprite sprite;
	Player();
	Player(FG::InputManager* inputManager, FG::Sprite sprite);

	void Update(float deltaTime) override;
	void Render(Renderer* const renderer) override;
	void Shoot(float deltaTime);
	SDL_Rect GetColliderRectangle();
	void OnCollision(FG::Entity* other) override;

private:
	FG::InputManager* inputManager = nullptr;
	FG::Vector2D position;

	bool isColliding = false;
	SDL_Color notCollidingColor = { 0, 255, 0, 255 };
	SDL_Color CollidingColor = { 255, 0, 0, 255 };

	void DrawBoundingBox();

	bool usingLight = false;
	void MovePlayer(float deltaTime);
};
