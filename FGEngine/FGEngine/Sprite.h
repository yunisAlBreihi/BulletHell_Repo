#pragma once

#include "IResource.h"
#include "Vector2D.h"
#include <SDL.h>

#include <string>

namespace FG
{
	class Camera;
	class Sprite : public IResource
	{
	public:
		Vector2D size;
		SDL_Rect srcRect;

		void Dispose() override;

		bool LoadImage(SDL_Renderer* renderer, const std::string& filename);
		bool LoadImage(SDL_Renderer* renderer, const std::string& filename, Vector2D spritePos, Vector2D spriteSize);
		void Render(Camera* camera, Vector2D position,bool usingSpriteSheet=false);

	protected:
		SDL_Texture* texture = nullptr;

		Vector2D sheetPos;
	};
}
