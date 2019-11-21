#pragma once

#pragma warning( push )
#pragma warning (disable : 26812 )

#include "Vector2D.h"

#include <SDL_mouse.h>
#include <SDL_keycode.h>
#include <SDL_scancode.h>

namespace FG
{
	static class InputManager
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

		static float ElapsedKeyTime(SDL_Scancode key);
		static bool IsMouseButtonDown(unsigned int mouseButton) { return mouseButtons[mouseButton]; }
		static bool IsMouseButtonPressed(unsigned int mouseButton);
		static bool IsMouseButtonReleased(unsigned int mouseButton);
		static float ElapsedMouseButtonTime(unsigned int mouseButton);

	private:
		static const Uint8* keys;
		static bool mouseButtons[SDL_BUTTON_X2];

		static Uint8 lastKeys[256];
		static bool lastMouseButtons[SDL_BUTTON_X2];

		static unsigned int keyTimes[SDL_NUM_SCANCODES];
		static unsigned int mouseButtonTimes[SDL_BUTTON_X2];
	};
}
#pragma warning( pop )
