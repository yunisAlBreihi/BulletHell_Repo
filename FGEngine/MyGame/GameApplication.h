#pragma once

#include <Application.h>
#include <Time.h>
#include <memory>

namespace FG
{
	class Window;
}

class SceneStateMachine;
class Renderer;

class GameApplication : public FG::Application
{
public:
	virtual bool Initialize() override;
	virtual void Run() override;
	virtual void Shutdown() override;

private:

	FG::Window* window = nullptr;
	std::unique_ptr<Renderer> renderer;
	FG::Time time;
	SceneStateMachine* sceneStateMachine;
};

FG::Application* FG::CreateApplication()
{
	return new GameApplication();
}


