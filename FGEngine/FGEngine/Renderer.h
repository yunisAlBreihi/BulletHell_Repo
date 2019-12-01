#pragma once
#include <SDL.h>
#include "Vector2D.h"
#include "float4.h"
#include <memory>
#include "Sprite.h"
#include "Color.h"
#include "float3.h"

#include "glew.h"
#include "wglew.h"
#include <vector>


#include "Shader.h"
#include "Camera.h"
#include "VBO.h"
#include "QuadVertex.h"
#include "LineVertex.h"
#include "SpriteVertex.h"
#include "TextVertex.h"
#include "Batch.h"

class Camera;
class RenderImpl;

class Renderer
{
private:
	Renderer();
	void ResetBatches();
	void Swap();
	void AddBatch(Batch batch) { batches.emplace_back(batch); }
public:
	~Renderer();
	Renderer(SDL_Window* window);
	void Clear(const float4& color);
	void Present(const Camera* const camera);

	void RenderQuad(const FG::Vector2D& position, const FG::Vector2D& size, const Color& fillColor, const Color& borderColor);
	void RenderText(const FG::Vector2D& position, const float size, const std::string& text);
	void Render(const FG::Vector2D& position, const FG::Sprite& sprite);
	void RenderLine(const FG::Vector2D& a, const FG::Vector2D& b, const float3& color, const float& size);


private:

	std::vector<SpriteVertex> vertices;
	std::vector<TextVertex> textVertices;
	std::vector<QuadVertex> quadVertices;
	std::vector<LineVertex> lineVertices;
	std::vector<Batch> batches;
	SDL_Window* window;

	Batch spriteBatch;
	Batch quadBatch;
	Batch lineBatch;
	Batch textBatch;

	VBO vbo;
	VBO quadVBO;
	VBO lineVBO;
	VBO textVBO;

	Shader quadShader;
	Shader shader;
	Shader lineShader;
	Shader textShader;
};


