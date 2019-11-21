#include "Application.h"
#include "Logger.h"

#include <cassert>
#include <SDL_main.h>

#include "BasicRandom.h"
#include <iostream>
extern FG::Application* FG::CreateApplication();

int main(int argc, char* argv[])
{
	for (int i = 0; i < 10; i++)
	{
		int v = BasicRandom::Range(0, 10);
		std::cout << v << '\n';
	}


	for (int i = 0; i < 10; i++)
	{
		int v = BasicRandom::Range(0, 100);
		std::cout << v << '\n';
	}


	for (int i = 0; i < 10; i++)
	{
		float v = BasicRandom::Range(0.0f, 10.0f);
		std::cout << v << '\n';
	}


	for (int i = 0; i < 10; i++)
	{
		float v = BasicRandom::Range(0.0f, 100.0f);
		std::cout << v << '\n';
	}

	SDL_LogSetOutputFunction(&FG::Logger::LogSDL, nullptr);
	SDL_SetMainReady();
	FG::Application* application = FG::CreateApplication();
	assert(application);

	if (!application->Initialize())
	{
		application->Shutdown();
		delete application;
		application = nullptr;
		return -1;
	}

	application->Run();
	application->Shutdown();
	delete application;
	application = nullptr;

	return 0;
}
