#include "HighScore.h"
#include "EntityManager.h"
#include <iostream>


HighScore::HighScore()
{
	std::cout << "Score is: " + score;
}

HighScore::~HighScore()
{
	ClearScore();
}

void HighScore::Update(float deltatime)
{
	std::cout << "Score is: ";
}

void HighScore::AddScore(int addScore)
{
	score += addScore;
	
}

int HighScore::MulitplyScore(int inputModifier)
{
	score = pow(score, inputModifier);
	return score;
}

void HighScore::ClearScore()
{
	score = 0;
}

