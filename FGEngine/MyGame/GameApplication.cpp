
#include "GameApplication.h"
#include <Window.h>
#include <InputManager.h>
#include <Camera.h>
#include <EntityManager.h>

#include <stdlib.h>
#include <Logger.h>
#include <SDL.h>

#include "GameState.h"
#include "StateMachine.h"
#include "InputManager.h"

#include "Renderer.h"
#include "SDL_syswm.h"
#include "Profiler.h"
#include "MyTestScene.h"
#include "StartMenuState.h"


bool GameApplication::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO |SDL_INIT_GAMECONTROLLER) < 0)
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	window = new FG::Window();
	if (!window->Initialize("My game", 1024, 576))
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}
	FG::InputManager::Initialize();
	renderer = std::make_unique<Renderer>(window->GetInternalWindow());
	loader.Init();
	loader.LoadFont("..//assets//fonts//Bebas-Regular.ttf", 12);
	sceneStateMachine = new SceneStateMachine(new GameState());
	return true;
}

const float WORLD_SIZE = 20.0f;
const FG::Vector2D worldMiddle = FG::Vector2D(1.0f, 1.0f);

void GameApplication::Run()
{
	Camera camera = Camera({ 0, 0, -1 }, NULL, -1, 100, WORLD_SIZE);
	bool quit = false;
	Profiler frameTime = Profiler();
	float fpsAccu = 0;
	int fpsCounter =0;
	while (!quit)
	{
		time.StartFrame();
		frameTime.Start("frameTime", false);
		FG::InputManager::Update(quit);
		if (FG::InputManager::IsKeyPressed(SDL_SCANCODE_RETURN) && FG::InputManager::IsKeyDown(SDL_SCANCODE_LALT))
		{
			if (window->IsMaximized())
			{
				window->Restore();
			}
			else
			{
				window->Maximize();
			}
		}

		if (!sceneStateMachine->Update(time.DeltaTime())) break; //if there is no scene to update, the application should quit
		sceneStateMachine->Render(renderer.get());
		camera.Update(time.DeltaTime(), worldMiddle);
		renderer->Clear(float4(0.0f, 0.0f, 0.0f, 1.0f));
		renderer->Present(&camera);
		fpsAccu += frameTime.End();
		fpsCounter++;
		if (fpsAccu >= 1.0f)
		{
			std::cout << "FPS: " << fpsCounter << std::endl;
			fpsAccu = 0;
			fpsCounter = 0;
		}
		time.EndFrame();
	}
}

void GameApplication::Shutdown()
{
	if (sceneStateMachine)
	{
		delete sceneStateMachine;
		sceneStateMachine = nullptr;
	}

	if (window)
	{
		window->Shutdown();
		delete window;
		window = nullptr;
	}

	Texture2DHandler::UnloadTextureArray();
	

	SDL_Quit();
}

