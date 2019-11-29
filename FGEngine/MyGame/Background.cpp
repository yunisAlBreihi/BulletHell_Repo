#include "Background.h"
#include "Renderer.h"
//#include <stb_image.h>
//#include <SDL_stbimage.h>
#include "Window.h"

Background::Background(FG::Sprite sprite)
{
	this->sprite = sprite;
	//this->sprite.size = { 30 * FG::Window::aspectRatio, 30 * FG::Window::aspectRatio };
}

Background::Background()
{

}

Background::~Background()
{

}

void Background::Disable()
{
	isActive = false;
}

void Background::Start(FG::Vector2D position)
{
	Entity::Start();
	this->position = position;
	//sprite.SetScale(FG::Vector2D)
}

void Background::Update(float deltaTime)
{

	ImageLoop(deltaTime);
}

void Background::OnCollision(FG::Entity* other)
{
}


void Background::Render(Renderer* const renderer)
{
	renderer->Render(position, sprite);
}

void Background::ImageLoop(float deltaTime)
{
	position.x -= deltaTime * speed;

	if (position.x < -42.0f)
	{
		position.x = 0.0f;
	}
}