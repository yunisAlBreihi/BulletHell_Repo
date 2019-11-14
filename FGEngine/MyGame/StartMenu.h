#pragma once
#include "Entity.h"

class StartMenu : public FG::Entity
{
public:
	FG::Sprite sprite;
	FG::Vector2D position;
	StartMenu(FG::Vector2D position, FG::Sprite sprite);
	void Update(float deltaTime) override;
	void Render(Renderer* const camera) override;

};

