#pragma once

#include <Application.h>
#include <Time.h>
#include <memory>

namespace FG
{
	class Window;
	class InputManager;
	class EntityManager;
	class ResourceManager;
}

class Camera;
class Renderer;
class Player;

class GameApplication : public FG::Application
{
public:
	virtual bool Initialize() override;
	virtual void Run() override;
	virtual void Shutdown() override;

private:
	FG::Window* window = nullptr;
	FG::InputManager* inputManager = nullptr;
	FG::EntityManager* entityManager = nullptr;
	FG::ResourceManager* resourceManager = nullptr;
	std::unique_ptr<Renderer> renderer;
	FG::Time time;
	Player* player1;
	Camera* camera;

};

FG::Application* FG::CreateApplication()
{
	return new GameApplication();
}
