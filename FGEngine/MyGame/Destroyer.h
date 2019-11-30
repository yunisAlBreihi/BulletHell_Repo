#pragma once
#include "Entity.h"
#include "BasicTimer.h"
#include "Vector2D.h"
#include "Sprite.h"
#include "EntityManager.h"
class Renderer;

class Destroyer : public FG::Entity {

public:
	Destroyer(FG::Sprite lightSprite, FG::Sprite darkSprite);
	~Destroyer() {}

	void Start(FG::Vector2D position);
	void Disable()override;

	void Update(float deltaTime)override;
	void Render(Renderer* const renderer)override;
	void OnCollision(FG::Entity* other)override;

	void Shoot(FG::EntityManager* entityManager, FG::Vector2D startPos, float baseAngle, float angleOffset);

	int health;

private:
	FG::Vector2D position;
	FG::Sprite currentSprite;
	FG::Sprite lightSprite;
	FG::Sprite darkSprite;
	bool usingLight;

	float spinRadius = 10;
	float spawnRate = 0.4f;
	float angleOffset = 0.0f;
	float spinSpeed = 1.15f;
	float projectileSpeed = 4.0f;
	
	bool reverse;

	float reverseAccu = 0;
	float direction;
	float spawnAccu = 0;
	float projectileCount = 25;
	const static int MAX_HEALTH = 2000;

	BasicTimer animationTimer;

	float healthBarWidth;
	float healthBarStepWidth;
};