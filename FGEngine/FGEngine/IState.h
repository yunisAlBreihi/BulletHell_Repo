#pragma once

class Renderer;

class IState
{
public:
	virtual ~IState() = default;
	virtual IState* NextState() { return nullptr; }
	virtual bool Update(float deltaTime) { return false; }
	virtual void OnExit(){}
	virtual void OnEnter(){}
};

class ISceneState : public IState
{
public:
	virtual void Render(Renderer* renderer) {}
};