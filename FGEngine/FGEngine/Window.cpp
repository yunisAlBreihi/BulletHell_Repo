#include "Window.h"
#include "Logger.h"

#include <SDL_video.h>

namespace FG
{
	float Window::aspectRatio = 0.0f;

	bool Window::Initialize(const std::string& title, int width, int height)
	{
		window = SDL_CreateWindow(title.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (!window)
		{
			FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
			return false;
		}

		aspectRatio = (float)width / (float)height;

		return true;
	}

	void Window::Shutdown()
	{
		if (window)
		{
			SDL_DestroyWindow(window);
			window = nullptr;
		}
	}

	void Window::SetTitle(const std::string& title)
	{
		SDL_SetWindowTitle(window, title.c_str());
	}

	void Window::SetSize(int width, int height)
	{
		aspectRatio = (float)width / (float)height;

		SDL_SetWindowSize(window, width, height);
	}
}
