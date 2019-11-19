#pragma once
#include "Entity.h"

namespace FG
{
	class InputManager;
}
class StartMenu : public FG::Entity
{
public:
	FG::Sprite sprite;
	FG::Vector2D position;
	StartMenu(FG::Vector2D position, FG::Sprite sprite, FG::InputManager* inputRef);
	FG::InputManager* mouseInput;
	int selectedMode;

	void Update(float deltaTime) override;
	void Render(Renderer* const camera) override;
	void ChangeMode(int change);
};

