#pragma once
#include <SDL.h>
#include "Vector2D.h"
#include "float4.h"
#include <memory>
#include "Sprite.h"
#include "Color.h"

class Camera;
class RenderImpl;

class Renderer
{
	std::unique_ptr<RenderImpl> renderImpl;	
public:
	Renderer(SDL_Window* window);
	~Renderer();
	void Clear(const float4& color);
	void Render(const FG::Vector2D& position, const FG::Sprite& sprite);
	void RenderQuad(const FG::Vector2D& position, const FG::Vector2D& size, const Color& color, const Color& fillColor);
	void RenderText(const FG::Vector2D& position, const int textSize, const std::string& text);
	void Present(const Camera *const camera);
};

