#pragma once
#include "Entity.h"
#include "StateMachine.h"
#include "BasicTimer.h"
#include "Vector2D.h"
#include "Sprite.h"
class Renderer;

class Destroyer : public FG::Entity {

public:
	Destroyer(FG::Sprite sprite);

	~Destroyer() {}

	void Start(FG::Vector2D position);
	void Disable()override;

	void Update(float deltaTime)override;
	void Render(Renderer* const renderer)override;
	void OnCollision(FG::Entity* other)override;


private:
	FG::Vector2D position;
	FG::Sprite sprite;

	float spinRadius = 10;
	float spawnRate = 0.15f;
	float angleOffset = 0.0f;
	float spinSpeed = 1.15f;
	float projectileSpeed = 8.0f;
	
	bool reverse;

	float reverseAccu = 0;
	float direction;
	float spawnAccu = 0;
	float projectileCount = 5;

};