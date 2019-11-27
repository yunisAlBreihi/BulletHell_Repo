#pragma once
#include <Entity.h>
#include <Vector2D.h>
#include "Sprite.h"
#include "Renderer.h"


class StartButton : public FG::Entity
{
public:
	StartButton(FG::Sprite sprite);
	~StartButton(){}

	void Start(FG::Vector2D startPos, int index);
	void Update(float deltaTime) override;
	void Render(Renderer* renderer) override;
	
	FG::Sprite sprite;
	FG::Vector2D position;

};

