#pragma once
#include "IState.h"

class Renderer;
class GameStateMachine;

class StateMachine
{
public:
	virtual ~StateMachine() = default;
	virtual bool Update(float deltaTime) = 0;
private:
	virtual bool SetState(IState* nextState) = 0;
};

class SceneStateMachine : public StateMachine
{
public:
	~SceneStateMachine() { currentState->OnExit(); delete currentState; currentState = nullptr; }
	SceneStateMachine(ISceneState* startState);
	void Render(Renderer* renderer);
	bool Update(float deltaTime) override;

private:
	bool SetState(IState* nextState) override;
	ISceneState* currentState;
};