#include "Sprite.h"
#include "Logger.h"
#include "Camera.h"

#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_stbimage.h>

namespace FG
{
	void Sprite::Dispose()
	{
		if (texture)
		{
			SDL_DestroyTexture(texture);
			texture = nullptr;
		}
	}

	bool Sprite::LoadImage(SDL_Renderer* renderer, const std::string& filename)
	{
		Dispose();
		SDL_Surface* surface = STBIMG_Load(filename.c_str());
		if (surface)
		{
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			if (!texture)
			{
				Logger::Log(SDL_GetError(),
					Logger::RemovePathFromFile(__FILE__), __LINE__);
				SDL_FreeSurface(surface);
				return false;
			}
			else
			{
				int width = 0;
				int height = 0;
				SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
				size.x = (float)width;
				size.y = (float)height;
				SDL_FreeSurface(surface);
				return true;
			}
		}
		else
		{
			Logger::Log("Error: Failed to log file " + filename,
				Logger::RemovePathFromFile(__FILE__), __LINE__);
			return false;
		}
	}

	void Sprite::Render(Camera* camera, Vector2D position)
	{
		Vector2D finalPosition = position - camera->position;
		SDL_Rect finalRect = SDL_Rect{(int)finalPosition.x, (int)finalPosition.y,
		(int)size.x, (int)size.y};
		SDL_RenderCopy(camera->GetInternalRenderer(), texture, nullptr, &finalRect);
	}
}
