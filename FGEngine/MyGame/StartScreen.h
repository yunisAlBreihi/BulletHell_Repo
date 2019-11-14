#pragma once
#include "InputManager.h"
#include "Texture2D.h"

class StartScreen 
{
public:
	StartScreen();
	~StartScreen ();


	Texture2D* startButton;

	void Update();
	void Render();

private:
	
};

StartScreen ::StartScreen ()
{
}

StartScreen ::~StartScreen ()
{
}