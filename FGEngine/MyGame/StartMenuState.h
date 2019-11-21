#pragma once
#include "IState.h"
class StartMenuState : public IState
{
	IState* NextState() override;
	bool Update(float deltaTime)  override;
	void OnExit() override;
	void OnEnter() override;
};