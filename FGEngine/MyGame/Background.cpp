#include "Background.h"
#include <stb_image.h>
#include <SDL_stbimage.h>


Background::Background(std::string filePath, SDL_Window* window, SDL_Renderer* renderer) :
	window(window), renderer(renderer)
{
	SDL_Surface* surface = STBIMG_Load(filePath.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	srcRect = { 0,0,width / 2,height };
}

Background::Background()
{
}

Background::~Background()
{
	//SDL_DestroyTexture(texture);
	//texture = nullptr;
}

void Background::Update()
{
	srcRect.x += 1;
	if (srcRect.x >= width / 2)
		srcRect.x = 0;

	Render();
}

void Background::Render()
{
	SDL_RenderCopy(renderer, texture, &srcRect, NULL);
}
