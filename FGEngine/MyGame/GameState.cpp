#include "GameState.h"
#include "StartMenuState.h"
#include <Sprite.h>
#include "Player.h"
#include "BaseEnemy.h"
#include "EnemyTypes.h"
#include "EnemySpawnManager.h"
#include "CollisionSystem.h"
#include "Background.h"

GameState::~GameState()
{
	if (entityManager)
	{
		entityManager->Shutdown();
	}
}

void GameState::OnEnter()
{
	FG::SpriteFactory factory;
	FG::Sprite playerSpriteLight = factory.LoadSprite("..//assets//images//lightning-blue.png", 1, 4, 0);
	FG::Sprite playerSpriteDark = factory.LoadSprite("..//assets//images//lightning-purple.png", 1, 4, 0);
	FG::Sprite lightBulletSprite = factory.LoadSprite("..//assets//images//projectile-blue.png", 1, 1, 0);
	FG::Sprite darkBulletSprite = factory.LoadSprite("..//assets//images//projectile-purple.png", 1, 1, 0);

	lightBulletSprite.SetScale(0.5f, 0.5f);
	darkBulletSprite.SetScale(0.5f, 0.5f);

	FG::Sprite sprite4 = factory.LoadSprite("..//assets//images//DarkSprites01.png", 8, 8, 5);

	FG::Sprite backgroundSprite = factory.LoadSprite("..//assets//images//bg.png", 1, 1);

	backgroundSprite.SetScale(56, 14);

	entityManager = FG::EntityManager::Instance();
	entityManager->InitializeEntityArray<Background>(2, backgroundSprite);
	entityManager->InitializeEntityArray<Player>(1, playerSpriteLight, playerSpriteDark);
	entityManager->InitializeEntityArray<DarkBullet>(1000, darkBulletSprite);
	entityManager->InitializeEntityArray<LightBullet>(1000, lightBulletSprite);

	player = entityManager->CreateEntity<Player>(FG::Vector2D(1, 1), 0);

	enemySpawnManager = new EnemySpawnManager();

	auto instance = CollisionSystem::GetInstance();
	instance->Setup(20, 20, 2);
	collisionSystemInstance = CollisionSystem::GetInstance();

	entityManager->CreateEntity<Background>(FG::Vector2D(0, 0));

}

bool GameState::Update(float deltaTime)
{
	entityManager->Update(deltaTime);
	enemySpawnManager->Update(deltaTime);
	collisionSystemInstance->TestCollisions();
//#ifndef _DEBUG
	if (player->IsDead())
	{
		return false;
	}
//#endif // _DEBUG
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
	return new GameState;
}

