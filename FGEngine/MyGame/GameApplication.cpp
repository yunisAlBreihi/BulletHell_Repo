
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
	FG::Sprite sprite3 = factory.LoadSprite("..//assets//images//DarkSprites01.png", 8, 8);
	FG::Sprite sprite4 = factory.LoadSprite("..//assets//images//DarkSprites01.png", 8, 8);
	entityManager = new FG::EntityManager();/*
	Enemy* enemy = new Enemy({5.0f,0}, sprite3, sprite3);
	entityManager->AddEntity(enemy);

	enemy = new Enemy({ 1.0f,0 }, sprite3, sprite3);
	entityManager->AddEntity(enemy);
	enemy = new Enemy({ 2.0f,0 }, sprite3, sprite3);
	entityManager->AddEntity(enemy);

	enemy = new Enemy({ 3.0f,0 }, sprite3, sprite3);
	entityManager->AddEntity(enemy);

	Player* player = new Player(inputManager, sprite);
	entityManager->AddEntity(player);

	Obstacle* obstacle = new Obstacle(FG::Vector2D(3, 1), sprite2);
	entityManager->AddEntity(obstacle);*/

	entityManager->InitializeEntityArray<Player>(1, inputManager, sprite);
	entityManager->InitializeEntityArray<Enemy>(10);

	Player* player = entityManager->CreateEntity<Player>();
	Enemy* enemy1 = entityManager->CreateEntity<Enemy>(FG::Vector2D(3.0f, 3.0f));
	Enemy* enemy2 = entityManager->CreateEntity<Enemy>();
	Enemy* enemy3 = entityManager->CreateEntity<Enemy>();
	Enemy* enemy4 = entityManager->CreateEntity<Enemy>();
	Enemy* enemy5 = entityManager->CreateEntity<Enemy>();
	Enemy* enemy6 = entityManager->CreateEntity<Enemy>();

	//
//#undef LoadImage
//	resourceManager = new FG::ResourceManager();
//	FG::Sprite* sprite = new FG::Sprite();
//	sprite->SetImage(camera->GetInternalRenderer(), "sports_car.png");
//	resourceManager->AddResource("sports_car.png", sprite);
//
//	sprite = new FG::Sprite();
//	sprite->SetImage(camera->GetInternalRenderer(), "rocks.png");
//	resourceManager->AddResource("rocks.png", sprite);
//
	
//
//	Player* player = new Player(inputManager, camera);
//	player->sprite = resourceManager->GetResource<FG::Sprite>("sports_car.png");
//	entityManager->AddEntity(player);
//
//	Obstacle* obstacle = new Obstacle(camera);
//	obstacle->sprite = resourceManager->GetResource<FG::Sprite>("rocks.png");
//	obstacle->position.x = 500.0f;
//	obstacle->position.y = 500.0f;
//	entityManager->AddEntity(obstacle);
//	sprite = new FG::Sprite();
//	sprite->SetImage(camera->GetInternalRenderer(), "rocks.png");
//
//	auto tempSprite = new FG::Sprite();
//	tempSprite->SetImage(camera->GetInternalRenderer(), "rocks.png");
//	entityManager->AddEntity(new Enemy(FG::Vector2D(300, 300), sprite, tempSprite, camera));

	auto instance = CollisionSystem::GetInstance();
	instance->Setup(500, 500, 10);

	return true;
}

void GameApplication::Run()
{
	Profiler profiler;
	bool quit = false;
	int fps = 0;  
	float deltaTimeAccu = 0;


	while (!quit)
	{
		time.StartFrame();
		profiler.Start("frame time: ", false);
		inputManager->Update(quit);
		entityManager->Update(time.DeltaTime());

		//renderer->RenderText({ 0, 0 }, 16, std::string("Hello World! abcdefghjklmnopqrstuvwxyz . - , > < ! \" / # ¤ % & ( ) = + : ;"));
		auto instance = CollisionSystem::GetInstance();
		instance->TestCollisions();
		camera->Update(0.1f, FG::Vector2D(0, 0));
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
