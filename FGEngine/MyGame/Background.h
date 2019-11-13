#pragma once
#include <string>
#include <SDL.h>

class Background
{

public:
	Background(std::string filePath, SDL_Window* window, SDL_Renderer* renderer);
	Background();

	~Background();

	void Update();

private:
	SDL_Texture* texture = nullptr;
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Rect srcRect;

	int width{ 0 };
	int height{ 0 };

	void Render();

	
};