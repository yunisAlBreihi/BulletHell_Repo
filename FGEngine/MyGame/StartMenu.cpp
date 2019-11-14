#include "StartMenu.h"
#include "Camera.h"
#include "Sprite.h"
#include <SDL_render.h>

StartMenu::StartMenu(FG::Vector2D position, FG::Sprite sprite) : sprite(sprite), position(position)
{

}

void StartMenu::Render(Renderer* const camera)
{
	camera->Render(position, sprite);
}

void StartMenu::Update(float deltaTime)
{

}