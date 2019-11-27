#include "StartButton.h"
#include "Sprite.h"
#include "Vector2D.h"
#include "Camera.h"
#include "EntityManager.h"
#include <SDL_render.h>

StartButton::StartButton(FG::Sprite sprite, FG::Vector2D position) : sprite(sprite), position(position)
{

}

void StartButton::Start(FG::Vector2D startPos)
{

	Entity::Start();
}

void StartButton::Update(float deltaTime)
{

}

void StartButton::Render(Renderer* renderer)
{
	renderer->Render(position, sprite);
}
