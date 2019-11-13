#pragma once

#include <string>
#include "Vector2D.h"

struct SDL_Window;

namespace FG
{
	class Window
	{
	public:
		virtual ~Window() {}

		virtual bool Initialize(const std::string& title, int width, int height);
		virtual void Shutdown();

		void SetTitle(const std::string& title);
		void SetSize(int width, int height);

		SDL_Window* GetInternalWindow() const { return window; }

		static float aspectRatio;
		static FG::Vector2D GetSpriteSize(float width, float height)
		{
			return { width * aspectRatio, height * aspectRatio };
		}

	protected:
		SDL_Window* window = nullptr;
	};
}
