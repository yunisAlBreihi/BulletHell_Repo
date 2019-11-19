#pragma once

#include <Entity.h>
#include <Vector2D.h>
#include "Bullet.h"
#include "Sprite.h"
#include "BasicTimer.h"
#include "PlayerWeapon.h"
namespace FG
{
	class Window;
	class InputManager;
	class Sprite;
}

const static float PLAYER_SHOOT_TIMER = 0.05f;
const static int PLAYER_LIGHT_STATE = 0;
const static int PLAYER_DARK_STATE = 1;
const static int PLAYER_HEALTH = 10;
const static int PLAYER_START_STATE = PLAYER_LIGHT_STATE;
const static float PLAYER_MOVEMENTSPEED = 5.0f;
const static float PLAYER_BULLET_SPEED = 10.0f;
const static FG::Vector2D PLAYER_SHOOT_DIR = FG::Vector2D(1, 0);


class Player : public FG::Entity
{
public:
	Player(FG::InputManager* inputManager, FG::Sprite sprite);
	~Player() {}
	void Init();
	void Start(FG::Vector2D startPos);
	void Update(float deltaTime) override;
	void Render(Renderer* const renderer) override;
	void Shoot(float deltaTime);
	void OnCollision(FG::Entity* other) override;
	
	bool IsDead() const
	{
		return health <= 0; 
	}

private:
	FG::InputManager* inputManager = nullptr;
	void SwapMode();
	void MovePlayer(float deltaTime);

	FG::Sprite sprite;
	FG::Vector2D position;
	BasicTimer shootTimer;
	int health;
	int playerState;
	float movementSpeed;

};
