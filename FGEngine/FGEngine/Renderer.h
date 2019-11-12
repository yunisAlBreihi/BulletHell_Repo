#pragma once
#pragma once
#include <Windows.h>

#include "Vector2D.h"
//#include "GL/glew.h"
#include "float4.h"
#include <memory>
namespace FG
{
	class Camera;
}
class RenderImpl;

struct Sprite
{
	int textureIndex;
	int spriteIndex;
};

class Renderer
{
	std::unique_ptr<RenderImpl> renderImpl;	
public:
	Renderer(const HDC& window);
	~Renderer() = default;
	void Clear(const float4& color);
	void Render(const FG::Vector2D& position, const Sprite& sprite);
	void Present(const FG::Camera *const camera);
};
