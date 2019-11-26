#include "StartMenuState.h"
#include <Sprite.h>
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
	FG::SpriteFactory factory;
	FG::Sprite sprite = factory.LoadSprite("..//assets//images//Start.png");

}

void StartMenuState::Render(Renderer* renderer)
{

}
