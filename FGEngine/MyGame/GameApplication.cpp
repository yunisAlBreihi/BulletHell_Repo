
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
	FG::Sprite sprite = factory.LoadSprite("..//assets//images//test.png",  {0.125f , 0.125f , 8.f, 8.f});
	entityManager = new FG::EntityManager();
	Enemy* enemy = new Enemy({0.0f,0}, sprite, sprite);
	entityManager->AddEntity(enemy);




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
	instance->Setup(50000, 50000, 500);

	return true;
}

void GameApplication::Run()
{
	bool quit = false;
	while (!quit)
	{
		time.StartFrame();
		inputManager->Update(quit);
		entityManager->Update(time.DeltaTime());

		auto instance = CollisionSystem::GetInstance();
		instance->TestCollisions();
		camera->Update(0.1f, FG::Vector2D(0, 0));
		renderer->Clear(float4(0.0f, 0.0f, 0.0f, 1.0f));
		renderer->Present(camera);
		entityManager->Render(renderer.get());
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

	//if (camera)
	//{
	//	camera->Shutdown();
	//	delete camera;
	//	camera = nullptr;
	//}

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
