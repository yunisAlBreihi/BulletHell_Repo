#include "Background.h"
#include <Renderer.h>
//#include <stb_image.h>
//#include <SDL_stbimage.h>
#include "Window.h"

Background::Background(FG::Sprite sprite) : sprite(sprite)
{
	position = { 0,-32 };
	this->sprite.size = { 30 * FG::Window::aspectRatio, 30 * FG::Window::aspectRatio };
}

Background::Background()
{
}

Background::~Background()
{

}

void Background::Update(float deltaTime)
{

}


void Background::Render(Renderer* const renderer)
{
	renderer->Render(position, sprite);
}