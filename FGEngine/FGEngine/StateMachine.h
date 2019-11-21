#pragma once
#include "IState.h"
class StateMachine
{
public:
	bool Update(float deltaTime);
	void Draw();
private:
	bool SetState(IState* nextState);

	IState* currentState;
};

