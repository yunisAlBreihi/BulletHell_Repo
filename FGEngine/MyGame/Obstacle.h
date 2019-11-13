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
	FG::Sprite sprite;

	Obstacle(FG::Vector2D position, FG::Sprite sprite) :position(position), sprite(sprite) { this->sprite.size = { 0.5f, 0.5f }; }
	void Render(Renderer* const camera) override;

	void Update(float deltaTime);
	SDL_Rect GetColliderRectangle();
	void OnCollision(FG::Entity* other) override;

private:
	bool isColliding = false;
	SDL_Color notCollidingColor = { 0, 255, 0, 255 };
	SDL_Color CollidingColor = { 255, 0, 0, 255 };

	void DrawBoundingBox();
};

