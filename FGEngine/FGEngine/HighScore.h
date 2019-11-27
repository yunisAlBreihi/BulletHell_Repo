#pragma once
#include "EntityManager.h"

class HighScore : FG::Entity
{
public:
	HighScore();
	~HighScore();

	void Update(float deltatime) override;
	void AddScore(int addScore);
	virtual int MulitplyScore(int inputModifier);
	int score;
private:
	void ClearScore();

};

