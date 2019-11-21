#include "InputManager.h"

#include <SDL_events.h>
#include <SDL_timer.h>
#include "Window.h"
#include "glew.h"
#include <stdint.h>

namespace FG
{
#pragma region STATIC_INIT
	Vector2D InputManager::mousePosition;
	Vector2D InputManager::mouseMovement;
	const Uint8* InputManager::keys = nullptr;
	Uint8 InputManager::lastKeys[256] = { 0 };

	bool InputManager::mouseButtons[SDL_BUTTON_X2] = { false };
	bool InputManager::lastMouseButtons[SDL_BUTTON_X2] = { false };

	unsigned int InputManager::keyTimes[SDL_NUM_SCANCODES] = { 0 };
	unsigned int InputManager::mouseButtonTimes[SDL_BUTTON_X2] = { 0 };
#pragma endregion


	void InputManager::Initialize()
	{
		keys = SDL_GetKeyboardState(nullptr);
		std::copy(keys, keys + 256, lastKeys);
	}

	void InputManager::Update(bool& shouldQuit)
	{
		SDL_Event event;
		std::copy(keys, keys+256, lastKeys);
		keys = SDL_GetKeyboardState(nullptr);

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_MOUSEMOTION:
				mousePosition.x = (float)event.motion.x;
				mousePosition.y = (float)event.motion.y;
				mouseMovement.x = (float)event.motion.xrel;
				mouseMovement.y = (float)event.motion.yrel;
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseButtons[event.button.button] = true;
				mouseButtonTimes[event.button.button] = SDL_GetTicks();
				break;
			case SDL_MOUSEBUTTONUP:
				mouseButtons[event.button.button] = false;
				mouseButtonTimes[event.button.button] = 0;
				break;
			case SDL_QUIT:
				shouldQuit = true;
				break;
			case SDL_WINDOWEVENT:
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					int screen_width = event.window.data1;
					int screen_height = event.window.data2;
					glViewport(0, 0, screen_width, screen_height);
					Window::aspectRatio = (float)screen_height / (float)screen_width;
				}
			}
			break;
			}
		}
	}

	bool InputManager::IsKeyPressed(SDL_Scancode key)
	{
		if (keys[key])
		{ 
			if (!lastKeys[key])
			{
				return true;
			}
		}
		return false;
	}

	bool InputManager::IsKeyReleased(SDL_Scancode key)
	{
		if (lastKeys[key] && !keys[key])
		{ 
			return true; 
		}
		return false;
	}

	float InputManager::ElapsedKeyTime(SDL_Scancode key)
	{
		return (SDL_GetTicks() - keyTimes[key] * 0.001f);
	}

	bool InputManager::IsMouseButtonPressed(unsigned int mouseButton)
	{
		if (!lastMouseButtons[mouseButton] && mouseButtons[mouseButton])
		{ return true; }
		return false;
	}

	bool InputManager::IsMouseButtonReleased(unsigned int mouseButton)
	{
		if (lastMouseButtons[mouseButton] && !mouseButtons[mouseButton])
		{ return true; }
		return false;
	}

	float InputManager::ElapsedMouseButtonTime(unsigned int mousebutton)
	{
		return (SDL_GetTicks() - mouseButtonTimes[mousebutton] * 0.001f);
	}
}
