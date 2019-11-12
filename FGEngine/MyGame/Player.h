#pragma once

#include <Entity.h>
#include <Vector2D.h>

namespace FG
{
	class Window;
	class InputManager;
	class Camera;
	class Sprite;
}

class Player : public FG::Entity
{
public:
	float speed = 100.0f;
	FG::Sprite* sprite = nullptr;

	Player(FG::InputManager* inputManager, FG::Camera* camera);

	void Update(float deltaTime) override;
	void Render(FG::Camera* const camera) override;

	SDL_Rect GetColliderRectangle();
	void OnCollision(FG::Entity* other) override;

private:
	FG::InputManager* inputManager = nullptr;
	FG::Camera* camera = nullptr;

	FG::Vector2D position;

	bool isColliding = false;
	SDL_Color notCollidingColor = { 0, 255, 0, 255 };
	SDL_Color CollidingColor = { 255, 0, 0, 255 };

	Player() {}

	void DrawBoundingBox();
	void MovePlayer(float deltaTime);
	void MoveCamera(float deltaTime);
};
