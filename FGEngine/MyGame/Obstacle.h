#pragma once

#include <Entity.h>
#include <Vector2D.h>
#include <SDL_pixels.h>

namespace FG
{
	class Sprite;
}

class Obstacle : public FG::Entity
{
public:
	FG::Vector2D position;
	FG::Sprite* sprite = nullptr;

	Obstacle()  {}
	void Render(Renderer* const camera) override;

	SDL_Rect GetColliderRectangle();
	void OnCollision(FG::Entity* other) override;

private:
	bool isColliding = false;
	SDL_Color notCollidingColor = { 0, 255, 0, 255 };
	SDL_Color CollidingColor = { 255, 0, 0, 255 };

	void DrawBoundingBox();
};

