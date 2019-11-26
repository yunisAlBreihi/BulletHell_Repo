#pragma once

#pragma warning( push )
#pragma warning (disable : 26812 )

#include "Vector2D.h"

#include <SDL_mouse.h>
#include <SDL_keycode.h>
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <vector>
namespace FG
{
	static const int NUM_KEYS = 256;
	static const int MAX_NUM_GAMEPADS = 8;
	static const int NUM_GAMEPAD_AXES = 6;
	static const int NUM_GAMEPAD_BUTTONS = 16;

	struct GamepadAxes
	{
		int axis[NUM_GAMEPAD_AXES];
	};

	class InputManager
	{
	public:
		static Vector2D mousePosition;
		// Delta movement since last update.
		static Vector2D mouseMovement;

		static void Initialize();
		static void Update(bool& shouldQuit);

		static bool IsKeyDown(SDL_Scancode key) { return keys[key]; }
		static bool IsKeyPressed(SDL_Scancode key);
		static bool IsKeyReleased(SDL_Scancode key);

		static bool GetButtonDown(uint8_t gamePadIndex, SDL_GameControllerButton button);
		static bool GetButtonUp(uint8_t gamePadIndex, SDL_GameControllerButton button);
		static bool GetButton(uint8_t gamePadIndex, SDL_GameControllerButton button);
		static float GetGamepadAxis(uint8_t gamepadIndex, SDL_GameControllerAxis axis);
		
		static float ElapsedKeyTime(SDL_Scancode key);
		static bool IsMouseButtonDown(unsigned int mouseButton) { return mouseButtons[mouseButton]; }
		static bool IsMouseButtonPressed(unsigned int mouseButton);
		static bool IsMouseButtonReleased(unsigned int mouseButton);
		static float ElapsedMouseButtonTime(unsigned int mouseButton);

	private:
		static const Uint8* keys;
		static bool mouseButtons[SDL_BUTTON_X2];

		static Uint8 lastKeys[NUM_KEYS];
		static bool lastMouseButtons[SDL_BUTTON_X2];

		static unsigned int keyTimes[SDL_NUM_SCANCODES];
		static unsigned int mouseButtonTimes[SDL_BUTTON_X2];
		static Sint32 gameControllers[MAX_NUM_GAMEPADS];

		static Uint8 gamePadButtons[MAX_NUM_GAMEPADS][NUM_GAMEPAD_BUTTONS];
		static Uint8 lastGamePadButtons[MAX_NUM_GAMEPADS][NUM_GAMEPAD_BUTTONS];
		static GamepadAxes gamepadAxes[MAX_NUM_GAMEPADS];

		static SDL_GameController* gameControllerPointers[MAX_NUM_GAMEPADS];

	};
}
#pragma warning( pop )
