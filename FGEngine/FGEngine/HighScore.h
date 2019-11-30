#pragma once
#include "EntityManager.h"

class HighScore : FG::Entity
{
public:
	static void AddScore(int addScore);
	static int GetScore();
	static void ResetScore();

private:
	HighScore();
	static int score;

};

