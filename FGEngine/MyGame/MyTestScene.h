#pragma once
#include "IState.h"
#include "IState.h"
#include "EntityManager.h"
#include "Spawner.h"
#include "BasicTimer.h"
#include "Renderer.h"
#include "EnemyDoubleWaveSweep.h"
#include "Player.h"
#include "CollisionSystem.h"

class MyTestScene : public ISceneState
{
public:
	~MyTestScene();

	void OnEnter() override;
	bool Update(float deltaTime)  override;
	void Render(Renderer* renderer) override;
	IState* NextState()  override;
	void OnExit() override;

private:
	FG::EntityManager* entityManager;
	BasicTimer DoubleWaveSweepTimer;
	Spawner<EnemyDoubleWaveSweep> DoubleWaveSweepSpawner;
	float DoubleWaveSweepMaxTime = 0.3f;
	Player* player;
	float spawnTimer = 0;

	CollisionSystem* collisionSystemInstance;

	template<typename T>
	void SpawnWaves(float dt, Spawner<T>* spawner, BasicTimer* timer, FG::Vector2D spawnPosition);

	void SpawnXTimes(float deltaTime, float& spawnTimer, float minSpawnTime, float spawnerMaxTime, int spawnCount, FG::Vector2D spawnPosition);
	void SpawnXTimesRandom(float deltaTime, float& spawnTimer, float spawnerMaxTime, int spawnCount, FG::Vector2D spawnPosition);
};