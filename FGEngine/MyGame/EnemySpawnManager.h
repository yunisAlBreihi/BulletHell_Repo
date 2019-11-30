#pragma once
#include "EnemySpawnParameters.h"
#include "EntityManager.h"
#include "BasicTimer.h"
#include "EnemyTypes.h"
#include "Destroyer.h"

class EnemySpawnManager
{
public:
	EnemySpawnManager();
	void Update(float deltaTime);

	template<typename T>
	void SpawnWaves(float dt, Spawner<T>* spawner, BasicTimer* timer, FG::Vector2D spawnPosition);

	template<typename T>
	bool SpawnXTimes(float& spawnTimer, float spawnerMaxTime, int spawnCount, Spawner<T>* spawner, BasicTimer* timer, FG::Vector2D spawnPosition, float deltaTime);

	template<typename T>
	void Spawn(EnemySpawnParameters* enemySpawn, Spawner<T>* spawner, BasicTimer* enemyTimer, int spawnCount, float deltaTime);

	void DestroyerSpawn(float deltaTime, float& maxSpawnTime);

private:
	FG::EntityManager* entityManager;
	BezierCurveManager* bezierCurveManager;

	Spawner<EnemyForwardDWaveL> enemyForwardDWaveLSpawner;
	Spawner<EnemyTripleCircularL> enemyTripleCircularLSpawner;
	Spawner<EnemyDWaveSweepB> enemyDWaveSweepBSpawner;
	Spawner<EnemyDVerticalWaveB> enemyDVerticalWaveBSpawner;
	Spawner<EnemyCircleStraightD> enemyCircleStraightDSpawner;
	Spawner<EnemyWaveStraightD> enemyWaveStraightDSpawner;

	float enemySpawnTime;
	EnemySpawnParameters* enemy01SpawnParameters;
	EnemySpawnParameters* enemy02SpawnParameters;
	EnemySpawnParameters* enemy03SpawnParameters;
	EnemySpawnParameters* enemy04SpawnParameters;
	EnemySpawnParameters* enemy05SpawnParameters;
	EnemySpawnParameters* enemy06SpawnParameters;

	BasicTimer enemy01Timer;
	BasicTimer enemy02Timer;
	BasicTimer enemy03Timer;
	BasicTimer enemy04Timer;
	BasicTimer enemy05Timer;
	BasicTimer enemy06Timer;

	//For the Destroyer boss spawn
	bool destroyerIsAlive;
	Destroyer* destroyer;
	float destroyerTimer;
	float destroyerMaxTimer;
};

