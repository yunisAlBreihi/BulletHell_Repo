#include "StateMachine.h"

bool StateMachine::Update(float deltaTime)
{
	if (!currentState->Update(deltaTime))
	{
		return SetState(currentState->NextState());
	}
	return true;
}

void StateMachine::Draw()
{
}

bool StateMachine::SetState(IState* nextState)
{
	currentState->OnExit();
	delete currentState;
	currentState = nullptr;


}
