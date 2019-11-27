#pragma once
#include "IState.h"
#include "Sprite.h"
#include "EntityManager.h"
#include "Renderer.h"
#include "StartButton.h"

class StartMenuState : public ISceneState
{
public:

	IState* NextState() override;
	~StartMenuState();
	
	void OnExit() override;
	void OnEnter() override;
	void Render(Renderer* renderer) override;
	bool Update(float deltaTime)  override;

private:
	FG::EntityManager* entityManager;
	StartButton* startButton;

};