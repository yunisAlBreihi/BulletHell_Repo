#pragma once

#include "IResource.h"
#include "Vector2D.h"

#include <string>

struct SDL_Texture;
struct SDL_Renderer;

namespace FG
{
	class Camera;
	class Sprite : public IResource
	{
	public:
		Vector2D size;
		
		void Dispose() override;

		bool LoadImage(SDL_Renderer* renderer, const std::string& filename);
		void Render(Camera* camera, Vector2D position);

	protected:
		SDL_Texture* texture = nullptr;
	};
}
