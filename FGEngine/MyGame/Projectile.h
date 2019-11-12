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
class Projectile : FG::Entity
{
public:
	float speed=200;
	FG::Sprite* sprite = nullptr;
	void Update(float deltaTime) override;
	void Render(FG::Camera* const camera) override;

	Projectile(FG::Camera* camera);

	SDL_Rect GetColliderRectangle();
	void OnCollision(FG::Entity* other) override;

	void SetPosition(FG::Vector2D pos);
	FG::Vector2D GetPosition() { return position; }

private:
	FG::Camera* camera = nullptr;
	FG::Vector2D position;

	bool isColliding=false;

	SDL_Color notCollidingColor = { 0, 255, 0, 255 };
	SDL_Color CollidingColor = { 255, 0, 0, 255 };

	Projectile() {}
	~Projectile();

	void DrawBoundingBox();
	void Move(float deltaTime);
};
