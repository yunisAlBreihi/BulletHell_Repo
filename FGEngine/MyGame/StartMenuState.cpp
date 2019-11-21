#include "StartMenuState.h"

IState* StartMenuState::NextState()
{
	return nullptr;
}

bool StartMenuState::Update(float deltaTime)
{
	return false;
}

void StartMenuState::OnExit()
{
}

void StartMenuState::OnEnter()
{
}

void StartMenuState::Render(Renderer* renderer)
{
}
