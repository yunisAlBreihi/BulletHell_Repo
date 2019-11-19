
#include "GameApplication.h"
#include <Window.h>
#include <InputManager.h>
#include <Camera.h>
#include <EntityManager.h>
#include <ResourceManager.h>
#include <Sprite.h>

#include <Logger.h>
#include <SDL.h>

#include "Player.h"
#include "BaseEnemy.h"
#include "EnemyWaveStraight.h"
#include "EnemyTripleCircular.h"
#include "EnemyDoubleWaveSweep.h"
#include "CollisionSystem.h"
#include "Renderer.h"
#include "SDL_syswm.h"
#include "Profiler.h"

bool GameApplication::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	window = new FG::Window();
	if (!window->Initialize("My game", 1024, 768))
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	inputManager = new FG::InputManager();
	inputManager->Initialize();

	renderer = std::make_unique<Renderer>(window->GetInternalWindow()); 
	FG::SpriteFactory factory;	
	FG::Sprite sprite = factory.LoadSprite("..//assets//images//bg.jpg", 1, 1);
	FG::Sprite sprite2 = factory.LoadSprite("..//assets//images//test.png", 8, 8);
	FG::Sprite sprite3 = factory.LoadSprite("..//assets//images//DarkSprites01.png", 8, 8, 1);
	FG::Sprite sprite4 = factory.LoadSprite("..//assets//images//DarkSprites01.png", 8, 8,5);
	FG::Sprite enemy01Sprite = factory.LoadSprite("..//assets//images//LightSprites01.png", 8, 8, 1);
	FG::Sprite enemy01BulletSprite = enemy01Sprite;
	enemy01BulletSprite.SetIndex(6);


	entityManager = FG::EntityManager::Instance();
	entityManager->InitializeEntityArray<Player>(1, inputManager, sprite3);
	entityManager->InitializeEntityArray<DarkBullet>(1000);
	entityManager->InitializeEntityArray<LightBullet>(1000);
	//Enemy01::Enemy01(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites, BulletSpreadType bulletSpreadType, MovementType movementType)
	entityManager->InitializeEntityArray<EnemyWaveStraight>(1, FG::Vector2D(0, 0), enemy01Sprite, enemy01BulletSprite, BaseEnemy::ShootWave, BaseEnemy::MoveStraight, BaseEnemy::Dark);
	entityManager->InitializeEntityArray<EnemyTripleCircular>(1, FG::Vector2D(0, 0), enemy01Sprite, enemy01BulletSprite, BaseEnemy::ShootTriple, BaseEnemy::MoveCircular, BaseEnemy::Light);
	entityManager->InitializeEntityArray<EnemyDoubleWaveSweep>(1, FG::Vector2D(0, 0), enemy01Sprite, enemy01BulletSprite, BaseEnemy::ShootDoubleWave, BaseEnemy::MoveSweep, BaseEnemy::Double);


	player1 = entityManager->CreateEntity<Player>(FG::Vector2D(1,1));
	EnemyWaveStraight* enemy02 = entityManager->CreateEntity<EnemyWaveStraight>(FG::Vector2D(20.0f, 8.0f));
	EnemyTripleCircular* enemy03 = entityManager->CreateEntity<EnemyTripleCircular>(FG::Vector2D(20.0f, 5.0f));
	EnemyDoubleWaveSweep* enemy04 = entityManager->CreateEntity<EnemyDoubleWaveSweep>(FG::Vector2D(20.0f, 7.0f));

	auto instance = CollisionSystem::GetInstance();
	instance->Setup(20, 20, 2);

	return true;
}

void GameApplication::Run()
{
	Camera camera = Camera({ 0, 0, -1 }, 45, -1, 100);
	Profiler profiler;
	bool quit = false;
	int fps = 0;  
	float deltaTimeAccu = 0;

	auto instance = CollisionSystem::GetInstance();
	while (!quit)
	{
		time.StartFrame();
		profiler.Start("frame time: ", false);
		inputManager->Update(quit);
		entityManager->Update(time.DeltaTime());
		instance->TestCollisions();
		camera.Update(0.1f, FG::Vector2D(1.0f, 1.0f));
		renderer->Clear(float4(0.0f, 0.0f, 0.0f, 1.0f));
		renderer->Present(&camera);
		entityManager->Render(renderer.get());

		deltaTimeAccu += profiler.End();
		if (deltaTimeAccu >= 1.0f)
		{
			std::cout << "FPS: " << fps << '\n';
			deltaTimeAccu = 0;
			fps = 0;
		}
		fps++;
		profiler.End();
		time.EndFrame();

	}
}

void GameApplication::Shutdown()
{
	if (entityManager)
	{
		entityManager->Shutdown();
		delete entityManager;
		entityManager = nullptr;
	}
	if (resourceManager)
	{
		resourceManager->Shutdown();
		delete resourceManager;
		resourceManager = nullptr;
	}


	if (inputManager)
	{
		delete inputManager;
		inputManager = nullptr;
	}

	if (window)
	{
		window->Shutdown();
		delete window;
		window = nullptr;
	}

	SDL_Quit();
}
