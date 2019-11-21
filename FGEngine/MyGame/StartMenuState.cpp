#include "StartMenuState.h"
#include "MyTestScene.h"
IState* StartMenuState::NextState()
{
	return new MyTestScene();
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
