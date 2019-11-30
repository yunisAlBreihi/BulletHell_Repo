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

	void Disable()override;
	void Start(FG::Vector2D position);
	void Update(float deltaTime) override;
	void OnCollision(FG::Entity* other)override;

private:
	FG::Sprite sprite;
	FG::Vector2D position;
	float speed;

	void Render(Renderer* const renderer) override;
	void ImageLoop(float deltaTime);

	
};