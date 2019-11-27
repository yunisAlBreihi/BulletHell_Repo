#include "StartMenuState.h"
#include <Sprite.h>
#include "MyTestScene.h"
#include "EntityManager.h"
#include "Camera.h"

IState* StartMenuState::NextState()
{
	return new MyTestScene();
}

StartMenuState::~StartMenuState()
{
}

void StartMenuState::OnEnter()
{
	FG::SpriteFactory factory;
	FG::Sprite sprite = factory.LoadSprite("..//assets//images//Start.png");

	entityManager = FG::EntityManager::Instance();
	entityManager->InitializeEntityArray<StartButton>(1, sprite);
	startButton = entityManager->CreateEntity<StartButton>(FG::Vector2D(5, 5), 0);
}

bool StartMenuState::Update(float deltaTime)
{
	entityManager->Update(deltaTime);
	return true;
}

void StartMenuState::Render(Renderer* renderer)
{
	entityManager->Render(renderer);
}

void StartMenuState::OnExit()
{
	if (entityManager)
	{
		entityManager->Shutdown();
	}
}
