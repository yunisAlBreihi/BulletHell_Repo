#include "EnemySpawnManager.h"
#include "BasicRandom.h"

EnemySpawnManager::EnemySpawnManager()
{
	enemySpawnTime = 0.6f;

	//For the destroyer Spawn
	destroyerTimer = 0.0f;
	destroyerMaxTimer = BasicRandom::Range(20.0f, 30.0f);
	destroyerIsAlive = false;

	enemy01Timer = BasicTimer(enemySpawnTime);
	enemy02Timer = BasicTimer(enemySpawnTime);
	enemy03Timer = BasicTimer(enemySpawnTime);
	enemy04Timer = BasicTimer(enemySpawnTime);
	enemy05Timer = BasicTimer(enemySpawnTime);
	enemy06Timer = BasicTimer(enemySpawnTime);

	bezierCurveManager = new BezierCurveManager();

	FG::SpriteFactory factory; //TODO: This is probably a mem leak

	FG::Sprite sprite4 = factory.LoadSprite("..//assets//images//DarkSprites01.png", 8, 8, 5);
	FG::Sprite enemy01SpriteL = factory.LoadSprite("..//assets//images//LightSprites02.png", 3, 3, 1);
	FG::Sprite enemy02SpriteL = factory.LoadSprite("..//assets//images//LightSprites02.png", 3, 3, 2);
	FG::Sprite enemy03SpriteD = factory.LoadSprite("..//assets//images//DarkSprites02.png", 3, 3, 3);
	FG::Sprite enemy04SpriteL = factory.LoadSprite("..//assets//images//LightSprites02.png", 3, 3, 4);
	FG::Sprite enemy05SpriteD = factory.LoadSprite("..//assets//images//DarkSprites02.png", 3, 3, 5);
	FG::Sprite enemy06SpriteD = factory.LoadSprite("..//assets//images//DarkSprites02.png", 3, 3, 6);

	FG::Sprite destroyerSpriteLight = factory.LoadSprite("..//assets//images//destroyer-blue.png", 1, 4, 0);
	FG::Sprite destroyerSpriteDark = factory.LoadSprite("..//assets//images//destroyer-purple.png", 1, 4, 0);
	destroyerSpriteDark.SetScale(2.0f, 2.0f);
	destroyerSpriteLight.SetScale(2.0f, 2.0f);

	entityManager = FG::EntityManager::Instance();
	entityManager->InitializeEntityArray<EnemyForwardDWaveL>(20, FG::Vector2D(0, 0), enemy01SpriteL, BaseEnemy::ShootForward, BaseEnemy::MoveDoubleWave, BaseEnemy::Light, bezierCurveManager);
	entityManager->InitializeEntityArray<EnemyTripleCircularL>(20, FG::Vector2D(0, 0), enemy02SpriteL, BaseEnemy::ShootTriple, BaseEnemy::MoveCircular, BaseEnemy::Light, bezierCurveManager);
	entityManager->InitializeEntityArray<EnemyDWaveSweepB>(20, FG::Vector2D(0, 0), enemy03SpriteD, BaseEnemy::ShootDoubleWave, BaseEnemy::MoveSweep, BaseEnemy::Both, bezierCurveManager);
	entityManager->InitializeEntityArray<EnemyDVerticalWaveB>(20, FG::Vector2D(0, 0), enemy04SpriteL, BaseEnemy::ShootDoubleVertical, BaseEnemy::MoveWave, BaseEnemy::Both, bezierCurveManager);
	entityManager->InitializeEntityArray<EnemyCircleStraightD>(20, FG::Vector2D(0, 0), enemy05SpriteD, BaseEnemy::ShootCircle, BaseEnemy::MoveStraight, BaseEnemy::Dark, bezierCurveManager);
	entityManager->InitializeEntityArray<EnemyWaveStraightD>(20, FG::Vector2D(0, 0), enemy06SpriteD, BaseEnemy::ShootWave, BaseEnemy::MoveStraight, BaseEnemy::Dark, bezierCurveManager);
	entityManager->InitializeEntityArray<Destroyer>(4, destroyerSpriteLight, destroyerSpriteDark);

	enemy01SpawnParameters = new EnemySpawnParameters(BasicRandom::Range(2.0f, 10.0f), FG::Vector2D(BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 8.0f)));
	enemy02SpawnParameters = new EnemySpawnParameters(BasicRandom::Range(2.0f, 10.0f), FG::Vector2D(BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 8.0f)));
	enemy03SpawnParameters = new EnemySpawnParameters(BasicRandom::Range(2.0f, 10.0f), FG::Vector2D(BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 8.0f)));
	enemy04SpawnParameters = new EnemySpawnParameters(BasicRandom::Range(2.0f, 10.0f), FG::Vector2D(BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 8.0f)));
	enemy05SpawnParameters = new EnemySpawnParameters(BasicRandom::Range(2.0f, 10.0f), FG::Vector2D(BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 8.0f)));
	enemy06SpawnParameters = new EnemySpawnParameters(BasicRandom::Range(2.0f, 10.0f), FG::Vector2D(BasicRandom::Range(20.0f, 22.5f), BasicRandom::Range(2.0f, 8.0f)));
}

void EnemySpawnManager::Update(float deltaTime)
{
	DestroyerSpawn(deltaTime,destroyerMaxTimer);

	if ( destroyerIsAlive && destroyer->health <= 0 )
	{
		destroyerIsAlive = false;
		destroyerTimer = 0;
	}

	if (!destroyerIsAlive)
	{
		Spawn(enemy01SpawnParameters, &enemyDWaveSweepBSpawner, &enemy01Timer, 3, deltaTime);
		Spawn(enemy02SpawnParameters, &enemyForwardDWaveLSpawner, &enemy02Timer, 1, deltaTime);
		Spawn(enemy03SpawnParameters, &enemyTripleCircularLSpawner, &enemy03Timer, 1, deltaTime);
		Spawn(enemy04SpawnParameters, &enemyDVerticalWaveBSpawner, &enemy04Timer, 1, deltaTime);
		Spawn(enemy05SpawnParameters, &enemyCircleStraightDSpawner, &enemy05Timer, 1, deltaTime);
		Spawn(enemy06SpawnParameters, &enemyWaveStraightDSpawner, &enemy06Timer, 1, deltaTime);
	}
}

template<typename T>
void EnemySpawnManager::Spawn(EnemySpawnParameters* enemySpawn, Spawner<T>* spawner, BasicTimer* enemyTimer, int spawnCount, float deltaTime)
{
	enemySpawn->timer += deltaTime;
	if (enemySpawn->timer > enemySpawn->timerMax)
	{
		enemySpawn->intervalTimer += deltaTime;

		if (SpawnXTimes(enemySpawn->intervalTimer, enemySpawnTime, spawnCount, spawner, enemyTimer, enemySpawn->position, deltaTime))
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

void EnemySpawnManager::DestroyerSpawn(float deltaTime, float& maxSpawnTime)
{
	destroyerTimer += deltaTime;

	if (destroyerTimer >= maxSpawnTime)
	{
		if (!destroyerIsAlive)
		{
			destroyer = entityManager->CreateEntity<Destroyer>(FG::Vector2D(10, 5));
			destroyerIsAlive = true;
			maxSpawnTime = BasicRandom::Range(20.0f, 30.0f);
		}
	}
}

