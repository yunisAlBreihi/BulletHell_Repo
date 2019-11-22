
#include "StartMenuState.h"
#include <Sprite.h>
#include "Player.h"
#include "BaseEnemy.h"
#include "EnemyWaveStraight.h"
#include "EnemyTripleCircular.h"
#include "EnemyDoubleWaveSweep.h"
#include "CollisionSystem.h"
#include "Destroyer.h"

#include "MyTestScene.h"

MyTestScene::~MyTestScene()
{
	entityManager->Shutdown();
}

void MyTestScene::OnEnter()
{
	FG::SpriteFactory factory; //TODO: This is probably a mem leak
	FG::Sprite playerSpriteLight = factory.LoadSprite("..//assets//images//lightning-blue.png", 1, 4, 0);
	FG::Sprite playerSpriteDark = factory.LoadSprite("..//assets//images//lightning-purple.png", 1, 4, 0);
	FG::Sprite lightBulletSprite = factory.LoadSprite("..//assets//images//projectile-blue.png", 1, 1, 0);
	FG::Sprite darkBulletSprite = factory.LoadSprite("..//assets//images//projectile-purple.png", 1, 1, 0);
	FG::Sprite destroyerSpriteLight = factory.LoadSprite("..//assets//images//destroyer-blue.png", 1, 4, 0);
	FG::Sprite destroyerSpriteDark = factory.LoadSprite("..//assets//images//destroyer-purple.png", 1, 4, 0);
	destroyerSpriteDark.SetScale(2.0f, 2.0f);
	destroyerSpriteLight.SetScale(2.0f, 2.0f);

	lightBulletSprite.SetScale(0.5f, 0.5f);
	darkBulletSprite.SetScale(0.5f, 0.5f);

	FG::Sprite sprite4 = factory.LoadSprite("..//assets//images//DarkSprites01.png", 8, 8, 5);
	FG::Sprite enemy01Sprite = factory.LoadSprite("..//assets//images//LightSprites01.png", 8, 8, 1);
	FG::Sprite enemy01BulletSprite = factory.LoadSprite("..//assets//images//LightSprites01.png", 8, 8, 6);

	entityManager = FG::EntityManager::Instance();
	entityManager->InitializeEntityArray<Player>(1, playerSpriteLight, playerSpriteDark);
	entityManager->InitializeEntityArray<DarkBullet>(7500, darkBulletSprite);
	entityManager->InitializeEntityArray<LightBullet>(7500, lightBulletSprite);
	//Enemy01::Enemy01(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites, BulletSpreadType bulletSpreadType, MovementType movementType)
	entityManager->InitializeEntityArray<EnemyWaveStraight>(20, FG::Vector2D(0, 0), enemy01Sprite, BaseEnemy::ShootCircle, BaseEnemy::MoveStraight, BaseEnemy::Dark);
	entityManager->InitializeEntityArray<EnemyTripleCircular>(20, FG::Vector2D(0, 0), enemy01Sprite, BaseEnemy::ShootTriple, BaseEnemy::MoveCircular, BaseEnemy::Light);
	entityManager->InitializeEntityArray<EnemyDoubleWaveSweep>(20, FG::Vector2D(0, 0), enemy01Sprite, BaseEnemy::ShootDoubleWave, BaseEnemy::MoveSweep, BaseEnemy::Double);
	entityManager->InitializeEntityArray<Destroyer>(4, destroyerSpriteLight, destroyerSpriteDark);
	player = entityManager->CreateEntity<Player>(FG::Vector2D(1, 1));

	//EnemyTripleCircular* enemy03 = entityManager->CreateEntity<EnemyTripleCircular>(FG::Vector2D(20.0f, 5.0f));
	//EnemyDoubleWaveSweep* enemy04 = entityManager->CreateEntity<EnemyDoubleWaveSweep>(FG::Vector2D(20.0f, 7.0f));

	EnemyWaveStraight* enemy02 = entityManager->CreateEntity<EnemyWaveStraight>(FG::Vector2D(20.0f, 8.0f));

	entityManager->CreateEntity<Destroyer>(FG::Vector2D(10, 5));
	entityManager->CreateEntity<Destroyer>(FG::Vector2D(10, 10));
	entityManager->CreateEntity<Destroyer>(FG::Vector2D(0, 5));
	entityManager->CreateEntity<Destroyer>(FG::Vector2D(15, 10));

	auto instance = CollisionSystem::GetInstance();
	instance->Setup(20, 20, 2);
	DoubleWaveSweepTimer = BasicTimer(DoubleWaveSweepMaxTime);
	collisionSystemInstance = CollisionSystem::GetInstance();
}

bool MyTestScene::Update(float deltaTime)
{
	spawnTimer += deltaTime;
	SpawnXTimes(deltaTime, spawnTimer, 4, DoubleWaveSweepMaxTime, 5, FG::Vector2D(25.0f, 5.0f));
	entityManager->Update(deltaTime);
	collisionSystemInstance->TestCollisions();
	if (player->IsDead())
	{
		return false;
	}
	return true;
}


void MyTestScene::Render(Renderer* renderer)
{
	entityManager->Render(renderer);
}

template<typename T>
inline void MyTestScene::SpawnWaves(float dt, Spawner<T>* spawner, BasicTimer* timer, FG::Vector2D spawnPosition)
{
	timer->Update(dt);
	if (timer->IsReady())
	{
	//	spawner->Execute(spawnPosition);
		timer->Use();
	}

}
void MyTestScene::SpawnXTimes(float deltaTime, float& spawnTimer, float minSpawnTime, float spawnerMaxTime, int spawnCount, FG::Vector2D spawnPosition)
{
	float maxSpawnTime = minSpawnTime + (spawnerMaxTime * spawnCount);
	if (spawnTimer > minSpawnTime&& spawnTimer < maxSpawnTime)
	{
		SpawnWaves(deltaTime, &DoubleWaveSweepSpawner, &DoubleWaveSweepTimer, spawnPosition);
	}
	if (spawnTimer > maxSpawnTime)
	{
		spawnTimer = 0;
	}
}


void MyTestScene::OnExit()
{

}

IState* MyTestScene::NextState()
{
	return new StartMenuState;
}

