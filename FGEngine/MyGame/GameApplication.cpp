
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
#include "Obstacle.h"
#include "Enemy.h"
#include "BaseEnemy.h"
#include "EnemyWaveStraight.h"
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

	camera = new Camera({0, 0, -1}, 45, -1, 100);

	FG::SpriteFactory factory;	
	FG::Sprite sprite = factory.LoadSprite("..//assets//images//bg.jpg", 1, 1);
	FG::Sprite sprite2 = factory.LoadSprite("..//assets//images//test.png", 8, 8);
	FG::Sprite sprite3 = factory.LoadSprite("..//assets//images//DarkSprites01.png", 8, 8, 1);
	FG::Sprite sprite4 = factory.LoadSprite("..//assets//images//DarkSprites01.png", 8, 8,5);
	FG::Sprite enemy01Sprite = factory.LoadSprite("..//assets//images//LightSprites01.png", 8, 8, 1);
	FG::Sprite enemy01BulletSprite = enemy01Sprite;
	enemy01BulletSprite.SetIndex(6);


	entityManager = FG::EntityManager::Instance();
	entityManager->InitializeEntityArray<Player>(4, inputManager, sprite3);
	entityManager->InitializeEntityArray<Enemy>(150);
	entityManager->InitializeEntityArray<BaseBullet>(10000);
	entityManager->InitializeEntityArray<LightBullet>(1000);
	//Enemy01::Enemy01(FG::Vector2D position, FG::Sprite sprite, FG::Sprite bulletsSprites, BulletSpreadType bulletSpreadType, MovementType movementType)
	entityManager->InitializeEntityArray<BaseEnemy>(1, FG::Vector2D(0,0), enemy01Sprite, enemy01BulletSprite, BaseEnemy::ShootCircle, BaseEnemy::MoveCircular);
	entityManager->InitializeEntityArray<EnemyWaveStraight>(1, FG::Vector2D(0, 0), enemy01Sprite, enemy01BulletSprite, EnemyWaveStraight::ShootWave, EnemyWaveStraight::MoveStraight);

	player1 = entityManager->CreateEntity<Player>();
	BaseEnemy* enemy01 = entityManager->CreateEntity<BaseEnemy>(FG::Vector2D(20.0f,6.0f));
	EnemyWaveStraight* enemy02 = entityManager->CreateEntity<EnemyWaveStraight>(FG::Vector2D(30.0f, 8.0f));

	
	 
	for (int i = 0; i < 10; i++)
	{
		Enemy* enemy1 = entityManager->CreateEntity<Enemy>(FG::Vector2D(0, (i % 10)), sprite2);
		Enemy* enemy2 = entityManager->CreateEntity<Enemy>(FG::Vector2D(9, (i % 10)), sprite3);
		Enemy* enemy3 = entityManager->CreateEntity<Enemy>(FG::Vector2D((i % 10), 0), sprite4);
		Enemy* enemy4 = entityManager->CreateEntity<Enemy>(FG::Vector2D((i % 10), 9), sprite4);
	}

	auto instance = CollisionSystem::GetInstance();
	instance->Setup(10, 10, 1);

	return true;
}

void GameApplication::Run()
{
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
		renderer->RenderLine(FG::Vector2D(1.0f, 0.0f), FG::Vector2D(3.0f, 0.0f), float3(1.0f, 1.0f, 1.0f), 0.01f);
		renderer->RenderLine(FG::Vector2D(3.0f, 3.0f), FG::Vector2D(3.6f, 2.5f), float3(0.8f, 0.0f, 0.3f), 0.01f);
		//renderer->RenderText({ 0, 0 }, 16, std::string("Hello World! abcdefghjklmnopqrstuvwxyz . - , > < ! \" / # ¤ % & ( ) = + : ;"));
		instance->TestCollisions();
		camera->Update(0.1f, FG::Vector2D(1.0f, 1.0f));
		renderer->Clear(float4(0.0f, 0.0f, 0.0f, 1.0f));
		renderer->Present(camera);
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

	if (camera)
	{
		delete camera;
		camera = nullptr;
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
