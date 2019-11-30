#pragma once
#include "IState.h"
#include "EntityManager.h"
#include "EnemySpawnManager.h"
#include "Spawner.h"
#include "BasicTimer.h"
#include "Renderer.h"
#include "EnemyTypes.h"
#include "Player.h"
#include "CollisionSystem.h"
#include "BezierCurveManager.h"
#include "HighScore.h"

class GameState : public ISceneState
{
public:
	~GameState();

	void OnEnter() override;
	bool Update(float deltaTime)  override; 
	void Render(Renderer* renderer) override;
	IState* NextState()  override;
	void OnExit() override;

private:
	FG::EntityManager* entityManager;
	EnemySpawnManager* enemySpawnManager;
	Player* player;
	CollisionSystem* collisionSystemInstance;
};

