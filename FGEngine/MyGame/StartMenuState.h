#pragma once
#include "IState.h"
class Renderer;

class StartMenuState : public ISceneState
{
	IState* NextState() override;
	bool Update(float deltaTime)  override;
	void OnExit() override;
	void OnEnter() override;
	void Render(Renderer* renderer) override;
};