#include "InputManager.h"

#include <SDL_events.h>
#include <SDL_timer.h>
#include "Window.h"
#include "glew.h"
#include <stdint.h>
#include <iostream>

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

	Sint32 InputManager::gameControllers[MAX_NUM_GAMEPADS] = {-1};

	Uint8 InputManager::gamePadButtons[MAX_NUM_GAMEPADS][NUM_GAMEPAD_BUTTONS] = { 0 };
	Uint8 InputManager::lastGamePadButtons[MAX_NUM_GAMEPADS][NUM_GAMEPAD_BUTTONS] = { 0 };
	GamepadAxes  InputManager::gamepadAxes[MAX_NUM_GAMEPADS] = {GamepadAxes()};

	SDL_GameController* InputManager::gameControllerPointers[MAX_NUM_GAMEPADS] = { nullptr };

#pragma endregion


	void InputManager::Initialize()
	{
		keys = SDL_GetKeyboardState(nullptr);
		std::copy(keys, keys + NUM_KEYS, lastKeys);

		for (int i = 0; i < MAX_NUM_GAMEPADS; i++)
		{
			gameControllers[i] = -1;
		}
	}

	void InputManager::Update(bool& shouldQuit)
	{
		SDL_Event event;
		std::copy(keys, keys+ NUM_KEYS, lastKeys);
		keys = SDL_GetKeyboardState(nullptr);
		
		for (int i = 0; i < MAX_NUM_GAMEPADS; i++)
		{
			std::copy(gamePadButtons[i], gamePadButtons[i] + NUM_GAMEPAD_BUTTONS, lastGamePadButtons[i]);
		}
		int numJoysticks = SDL_NumJoysticks();
		for (int i = 0; i < numJoysticks; i++)
		{
			if (SDL_IsGameController(i)) {
				gameControllerPointers[i] = SDL_GameControllerOpen(i);
			}
		}
		//TODO: move this to window, InputManager should have 0 (ZERO!) coupling or dependency to/with SDL. This is the reponsibility of the window, not the inputmanager...
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
			}break;
			case SDL_CONTROLLERDEVICEADDED:
			{
				int intellisensePlease = event.cdevice.which;
				gameControllerPointers[event.cdevice.which]  = SDL_GameControllerOpen(event.cdevice.which);
				std::cout << gameControllerPointers[event.cdevice.which] << std::endl;
				gameControllers[event.cdevice.which] = intellisensePlease;
			}break;
			case SDL_CONTROLLERDEVICEREMOVED:
			{
				for (int i = 0; i < MAX_NUM_GAMEPADS; i++)
				{
					if (event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gameControllerPointers[i])))
					{
						SDL_GameControllerClose(gameControllerPointers[i]);
						gameControllerPointers[i] = nullptr;
						gameControllers[i] = -1;
						break;
					}
				}
			}break;
			case SDL_CONTROLLERBUTTONDOWN:
			{			
				auto which = event.cdevice.which;
				for (int i = 0; i < MAX_NUM_GAMEPADS; i++)
				{
					if (event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gameControllerPointers[i])))
					{
						gamePadButtons[i][event.cbutton.button] = event.cbutton.state;
						break;
					}
				}
			}break;
			case SDL_CONTROLLERBUTTONUP:
			{
				for (int i = 0; i < MAX_NUM_GAMEPADS; i++)
				{
					if (event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gameControllerPointers[i])))
					{
						gamePadButtons[i][event.cbutton.button] = event.cbutton.state;
						break;
					}
				}
			}break;
			case SDL_CONTROLLERAXISMOTION:
			{
				for (int i = 0; i < MAX_NUM_GAMEPADS; i++)
				{
					if (event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gameControllerPointers[i])))
					{
						gamepadAxes[i].axis[event.caxis.axis] = event.caxis.value;
						break;
					}
				}
			}break;
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

	bool InputManager::GetButtonDown(uint8_t gamepadIndex, SDL_GameControllerButton button)
	{
		if (gameControllers[gamepadIndex] == -1)
		{
			return false;
		}
		return gamePadButtons[gameControllers[gamepadIndex]][button] && !lastGamePadButtons[gameControllers[gamepadIndex]][button];
	}

	bool InputManager::GetButtonUp(uint8_t gamepadIndex, SDL_GameControllerButton button)
	{
		if (gameControllers[gamepadIndex] == -1)
		{
			return false;
		}
		return !gamePadButtons[gameControllers[gamepadIndex]][button] && lastGamePadButtons[gameControllers[gamepadIndex]][button];
	}

	bool InputManager::GetButton(uint8_t gamepadIndex, SDL_GameControllerButton button)
	{
		if (gameControllers[gamepadIndex] == -1)
		{
			return false;
		}
		return gamePadButtons[gameControllers[gamepadIndex]][button];
	}

	float InputManager::GetGamepadAxis(uint8_t gamepadIndex, SDL_GameControllerAxis axis)
	{
		return gamepadAxes[gameControllers[gamepadIndex]].axis[axis];
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
