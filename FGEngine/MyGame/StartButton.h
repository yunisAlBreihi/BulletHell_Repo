#pragma once
#include <Entity.h>
#include <Vector2D.h>
#include "Sprite.h"
#include "Renderer.h"

namespace FG
{
	class window;
	class Sprite;
	class Renderer;
}
class StartButton : public FG::Entity
{
public:
	StartButton(FG::Sprite sprite, FG::Vector2D position);
	~StartButton(){}


	void Start(FG::Vector2D startPos);
	void Update(float deltaTime) override;
	void Render(Renderer* renderer) override;
	
	FG::Sprite sprite;
	FG::Vector2D position;
private:
	FG::Vector2D centerPos;

};

