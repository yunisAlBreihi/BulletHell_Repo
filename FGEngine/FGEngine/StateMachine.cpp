#include "StateMachine.h"

SceneStateMachine::SceneStateMachine(ISceneState* startState)
{
	currentState = startState;
	currentState->OnEnter();
}

void SceneStateMachine::Render(Renderer* renderer)
{
	currentState->Render(renderer);
}

bool SceneStateMachine::Update(float deltaTime)
{
	if (!currentState->Update(deltaTime))
	{
		return SetState(currentState->NextState());
	}
	return true;
}

bool SceneStateMachine::SetState(IState* nextState)
{
	if (nextState == nullptr)
	{
		return false;
	}

	currentState->OnExit();
	delete currentState;
	currentState = (ISceneState*)nextState;
	nextState->OnEnter();
	return true;
}
