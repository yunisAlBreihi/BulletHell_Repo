#include "HighScore.h"
#include "EntityManager.h"
#include <iostream>

int HighScore::score = 0;

void HighScore::AddScore(int addScore)
{
	score += addScore;
}

int HighScore::GetScore()
{
	return score;
}

void HighScore::ResetScore()
{
	score = 0;
}

