#pragma once

namespace FG
{
	class Renderer;
}

class IState
{
	friend class StateMachine;
private:
	virtual IState* NextState() { return nullptr; }
	virtual bool Update(float deltaTime) { return false; }
	virtual void Render(FG::Renderer* renderer){}
	virtual void OnExit(){}
	virtual void OnEnter(){}
};