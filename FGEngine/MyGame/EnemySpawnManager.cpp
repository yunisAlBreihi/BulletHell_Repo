#include "EnemySpawnManager.h"
#include "BasicRandom.h"

EnemySpawnManager::EnemySpawnManager()
{
	enemySpawnTime = 0.6f;
	enemyTimer = BasicTimer(enemySpawnTime);
	enemySpawn01 = new EnemySpawnParameters(BasicRandom::Range(2.0f, 10.0f), FG::Vector2D(BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 8.0f)));
	enemySpawn02 = new EnemySpawnParameters(BasicRandom::Range(2.0f, 10.0f), FG::Vector2D(BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 8.0f)));
	enemySpawn03 = new EnemySpawnParameters(BasicRandom::Range(2.0f, 10.0f), FG::Vector2D(BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 8.0f)));
	enemySpawn04 = new EnemySpawnParameters(BasicRandom::Range(2.0f, 10.0f), FG::Vector2D(BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 8.0f)));
	enemySpawn05 = new EnemySpawnParameters(BasicRandom::Range(2.0f, 10.0f), FG::Vector2D(BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 8.0f)));
	enemySpawn06 = new EnemySpawnParameters(BasicRandom::Range(2.0f, 10.0f), FG::Vector2D(BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 8.0f)));
}

void EnemySpawnManager::Update(float deltaTime)
{
	Spawn(enemySpawn01, &enemyDWaveSweepBSpawner, 5, deltaTime);
	Spawn(enemySpawn02, &enemyForwardDWaveLSpawner, 1, deltaTime);
	Spawn(enemySpawn03, &enemyTripleCircularLSpawner, 2, deltaTime);
	Spawn(enemySpawn04, &enemyDVerticalWaveBSpawner, 2, deltaTime);
	Spawn(enemySpawn05, &enemyCircleStraightDSpawner, 1, deltaTime);
	Spawn(enemySpawn06, &enemyWaveStraightDSpawner, 1, deltaTime);
}

template<typename T>
void EnemySpawnManager::Spawn(EnemySpawnParameters* enemySpawn, Spawner<T>* spawner, int spawnCount, float deltaTime)
{
	enemySpawn->timer += deltaTime;
	if (enemySpawn->timer > enemySpawn->timerMax)
	{
		enemySpawn->intervalTimer += deltaTime;

		if (SpawnXTimes(enemySpawn->intervalTimer, enemySpawnTime, spawnCount, spawner, &enemyTimer, enemySpawn->position, deltaTime))
		{
			enemySpawn->timerMax = BasicRandom::Range(2.0f, 15.0f);
			enemySpawn->position = { BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 10.0f) };
			enemySpawn->timer = 0;
		}
	}
}

template<typename T>
inline void EnemySpawnManager::SpawnWaves(float dt, Spawner<T>* spawner, BasicTimer* timer, FG::Vector2D spawnPosition)
{
	timer->Update(dt);
	if (timer->IsReady())
	{
		spawner->Execute(spawnPosition);
		timer->Use();
	}
}

template<typename T>
bool EnemySpawnManager::SpawnXTimes(float& spawnTimer, float timeBetweenSpawns, int spawnCount, Spawner<T>* spawner, BasicTimer* timer, FG::Vector2D spawnPosition, float deltaTime)
{
	float maxSpawnTime = (timeBetweenSpawns * spawnCount) - 0.1f;

	if (spawnTimer <= maxSpawnTime)
	{
		SpawnWaves(deltaTime, spawner, timer, spawnPosition);
	}
	if (spawnTimer > maxSpawnTime)
	{
		spawnTimer = 0;
		return true;
	}
	return false;
}

