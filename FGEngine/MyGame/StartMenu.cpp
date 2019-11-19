#include "StartMenu.h"
#include "Camera.h"
#include "Sprite.h"
#include "InputManager.h"
#include <SDL_render.h>
#include <iostream>

StartMenu::StartMenu(FG::Vector2D position, FG::Sprite sprite, FG::InputManager* inputRef) :position(position), sprite(sprite), mouseInput(inputRef)
{

}

void StartMenu::Render(Renderer* const camera)
{
	camera->Render(position, sprite);
}

void StartMenu::ChangeMode(int change)
{
	if (mouseInput-> IsMouseButtonPressed(0))
	{
		std::cout << "mouse 0 pressed";
		if ((mouseInput->mousePosition.x -= position) && (x < box.x + box.w) && (y > box.y) && (y < box.y + box.h))
		{

		}
	}
}

void StartMenu::Update(float deltaTime)
{
	
}