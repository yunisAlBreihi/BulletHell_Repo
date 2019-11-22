#pragma once
#include "EnemySpawnParameters.h"
#include "BasicTimer.h"
#include "EnemyTypes.h"

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
	void Spawn(EnemySpawnParameters* enemySpawn, Spawner<T>* spawner, int spawnCount, float deltaTime);

private:

	Spawner<EnemyForwardDWaveL> enemyForwardDWaveLSpawner;
	Spawner<EnemyTripleCircularL> enemyTripleCircularLSpawner;
	Spawner<EnemyDWaveSweepB> enemyDWaveSweepBSpawner;
	Spawner<EnemyDVerticalWaveB> enemyDVerticalWaveBSpawner;
	Spawner<EnemyCircleStraightD> enemyCircleStraightDSpawner;
	Spawner<EnemyWaveStraightD> enemyWaveStraightDSpawner;

	float enemySpawnTime;
	BasicTimer enemyTimer;
	EnemySpawnParameters* enemySpawn01;
	EnemySpawnParameters* enemySpawn02;
	EnemySpawnParameters* enemySpawn03;
	EnemySpawnParameters* enemySpawn04;
	EnemySpawnParameters* enemySpawn05;
	EnemySpawnParameters* enemySpawn06;
};

