#pragma once

#include <Entity.h>
#include <Vector2D.h>
#include <SDL_pixels.h>

namespace FG
{
	class Sprite;
	class Camera;
}

class Obstacle : public FG::Entity
{
public:
	FG::Vector2D position;
	FG::Sprite* sprite = nullptr;

	Obstacle(FG::Camera* camera) : camera(camera) {}
	void Render(FG::Camera* const camera) override;

	void Update(float deltaTime);
	SDL_Rect GetColliderRectangle();
	void OnCollision(FG::Entity* other) override;

private:
	bool isColliding = false;
	SDL_Color notCollidingColor = { 0, 255, 0, 255 };
	SDL_Color CollidingColor = { 255, 0, 0, 255 };
	FG::Camera* camera = nullptr;

	void DrawBoundingBox();
};

