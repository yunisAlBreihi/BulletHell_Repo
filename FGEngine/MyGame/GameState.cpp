#include "GameState.h"
#include "StartMenuState.h"
#include <Sprite.h>
#include "Player.h"
#include "BaseEnemy.h"
#include "EnemyTypes.h"
#include "EnemySpawnManager.h"
#include "CollisionSystem.h"
#include "WeaponPickup.h"
GameState::~GameState()
{
	if (entityManager)
	{
		entityManager->Shutdown();
	}


}

void GameState::OnEnter()
{
	FG::SpriteFactory factory; //TODO: This is probably a mem leak
	FG::Sprite playerSpriteLight = factory.LoadSprite("..//assets//images//lightning-blue.png", 1, 4, 0);
	FG::Sprite playerSpriteDark = factory.LoadSprite("..//assets//images//lightning-purple.png", 1, 4, 0);
	FG::Sprite lightBulletSprite = factory.LoadSprite("..//assets//images//projectile-blue.png", 1, 1, 0);
	FG::Sprite darkBulletSprite = factory.LoadSprite("..//assets//images//projectile-purple.png", 1, 1, 0);

	lightBulletSprite.SetScale(0.5f, 0.5f);
	darkBulletSprite.SetScale(0.5f, 0.5f);

	FG::Sprite sprite4 = factory.LoadSprite("..//assets//images//DarkSprites01.png", 8, 8, 5);
	FG::Sprite enemy01SpriteL = factory.LoadSprite("..//assets//images//LightSprites02.png", 3, 3, 1);
	FG::Sprite enemy01SpriteD = factory.LoadSprite("..//assets//images//DarkSprites02.png", 3, 3, 1);
	FG::Sprite enemy02SpriteL = factory.LoadSprite("..//assets//images//LightSprites02.png", 3, 3, 2);
	FG::Sprite enemy02SpriteD = factory.LoadSprite("..//assets//images//DarkSprites02.png", 3, 3, 2);
	FG::Sprite enemy03SpriteL = factory.LoadSprite("..//assets//images//LightSprites02.png", 3, 3, 3);
	FG::Sprite enemy03SpriteD = factory.LoadSprite("..//assets//images//DarkSprites02.png", 3, 3, 3);
	FG::Sprite enemy04SpriteL = factory.LoadSprite("..//assets//images//LightSprites02.png", 3, 3, 4);
	FG::Sprite enemy04SpriteD = factory.LoadSprite("..//assets//images//DarkSprites02.png", 3, 3, 4);
	FG::Sprite enemy05SpriteL = factory.LoadSprite("..//assets//images//LightSprites02.png", 3, 3, 5);
	FG::Sprite enemy05SpriteD = factory.LoadSprite("..//assets//images//DarkSprites02.png", 3, 3, 5);
	FG::Sprite enemy06SpriteL = factory.LoadSprite("..//assets//images//LightSprites02.png", 3, 3, 6);
	FG::Sprite enemy06SpriteD = factory.LoadSprite("..//assets//images//DarkSprites02.png", 3, 3, 6);

	entityManager = FG::EntityManager::Instance();
	entityManager->InitializeEntityArray<Player>(1, playerSpriteLight, playerSpriteDark);
	entityManager->InitializeEntityArray<DarkBullet>(1000, darkBulletSprite);
	entityManager->InitializeEntityArray<LightBullet>(1000, lightBulletSprite);

	entityManager->InitializeEntityArray<EnemyForwardDWaveL>(20, FG::Vector2D(0, 0), enemy01SpriteL, BaseEnemy::ShootForward, BaseEnemy::MoveDoubleWave, BaseEnemy::Light);
	entityManager->InitializeEntityArray<EnemyForwardDWaveD>(20, FG::Vector2D(0, 0), enemy01SpriteD, BaseEnemy::ShootForward, BaseEnemy::MoveDoubleWave, BaseEnemy::Dark);

	entityManager->InitializeEntityArray<WeaponPickup>(100, enemy01SpriteD);

	entityManager->InitializeEntityArray<EnemyTripleCircularL>(20, FG::Vector2D(0, 0), enemy02SpriteL, BaseEnemy::ShootTriple, BaseEnemy::MoveCircular, BaseEnemy::Light);
	entityManager->InitializeEntityArray<EnemyTripleCircularD>(20, FG::Vector2D(0, 0), enemy02SpriteD, BaseEnemy::ShootTriple, BaseEnemy::MoveCircular, BaseEnemy::Dark);
	entityManager->InitializeEntityArray<EnemyTripleCircularB>(20, FG::Vector2D(0, 0), enemy02SpriteL, BaseEnemy::ShootTriple, BaseEnemy::MoveCircular, BaseEnemy::Both);

	entityManager->InitializeEntityArray<EnemyDWaveSweepL>(20, FG::Vector2D(0, 0), enemy03SpriteL, BaseEnemy::ShootDoubleWave, BaseEnemy::MoveSweep, BaseEnemy::Light);
	entityManager->InitializeEntityArray<EnemyDWaveSweepD>(20, FG::Vector2D(0, 0), enemy03SpriteD, BaseEnemy::ShootDoubleWave, BaseEnemy::MoveSweep, BaseEnemy::Dark);
	entityManager->InitializeEntityArray<EnemyDWaveSweepB>(20, FG::Vector2D(0, 0), enemy03SpriteD, BaseEnemy::ShootDoubleWave, BaseEnemy::MoveSweep, BaseEnemy::Both);

	entityManager->InitializeEntityArray<EnemyDVerticalWaveL>(20, FG::Vector2D(0, 0), enemy04SpriteL, BaseEnemy::ShootDoubleVertical, BaseEnemy::MoveWave, BaseEnemy::Light);
	entityManager->InitializeEntityArray<EnemyDVerticalWaveD>(20, FG::Vector2D(0, 0), enemy04SpriteD, BaseEnemy::ShootDoubleVertical, BaseEnemy::MoveWave, BaseEnemy::Dark);
	entityManager->InitializeEntityArray<EnemyDVerticalWaveB>(20, FG::Vector2D(0, 0), enemy04SpriteL, BaseEnemy::ShootDoubleVertical, BaseEnemy::MoveWave, BaseEnemy::Both);

	entityManager->InitializeEntityArray<EnemyCircleStraightL>(20, FG::Vector2D(0, 0), enemy05SpriteL, BaseEnemy::ShootCircle, BaseEnemy::MoveStraight, BaseEnemy::Light);
	entityManager->InitializeEntityArray<EnemyCircleStraightD>(20, FG::Vector2D(0, 0), enemy05SpriteD, BaseEnemy::ShootCircle, BaseEnemy::MoveStraight, BaseEnemy::Dark);

	entityManager->InitializeEntityArray<EnemyWaveStraightL>(20, FG::Vector2D(0, 0), enemy06SpriteL, BaseEnemy::ShootWave, BaseEnemy::MoveStraight, BaseEnemy::Light);
	entityManager->InitializeEntityArray<EnemyWaveStraightD>(20, FG::Vector2D(0, 0), enemy06SpriteD, BaseEnemy::ShootWave, BaseEnemy::MoveStraight, BaseEnemy::Dark);

	player = entityManager->CreateEntity<Player>(FG::Vector2D(1, 1), 0);
	entityManager->CreateEntity<WeaponPickup>(FG::Vector2D(1.0f, 3.0f));

	enemySpawnManager = new EnemySpawnManager();

	auto instance = CollisionSystem::GetInstance();
	instance->Setup(20, 20, 2);
	collisionSystemInstance = CollisionSystem::GetInstance();
}

bool GameState::Update(float deltaTime)
{
	entityManager->Update(deltaTime);
	enemySpawnManager->Update(deltaTime);
	collisionSystemInstance->TestCollisions();
#ifndef _DEBUG
	if (player->IsDead())
	{
		return false;
	}
#endif // _DEBUG
	return true;
}


void GameState::Render(Renderer* renderer)
{
	entityManager->Render(renderer);
}

void GameState::OnExit()
{
	if (entityManager)
	{
		entityManager->Shutdown();
	}

}
IState* GameState::NextState()
{
	return new StartMenuState;
}

