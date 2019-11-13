#pragma once
#include <string>
#include <SDL.h>
#include <Sprite.h>
#include <Entity.h>	

class Background : public FG::Entity
{

public:
	Background(FG::Sprite sprite);
	Background();

	~Background();

	void Update(float deltaTime) override;

private:
	FG::Sprite sprite;

	FG::Vector2D position;

	int width{ 0 };
	int height{ 0 };

	void Render(Renderer* const renderer) override;

	
};