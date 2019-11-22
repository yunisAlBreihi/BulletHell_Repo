#pragma once
#include "Entity.h"
#include "Sprite.h"

class WeaponPickup : public FG::Entity
{
	WeaponPickup(FG::Sprite sprite);
	~WeaponPickup() {}

	void Start(FG::Vector2D position); // type, etc.
	void Update(float deltaTime) override;
	void Render(Renderer* const renderer) override;
	void OnCollision(Entity* other) override;

	FG::Sprite sprite;
	FG::Vector2D position;
};