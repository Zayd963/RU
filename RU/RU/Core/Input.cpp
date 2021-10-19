#include "Input.h"
#include <iostream>
#include <algorithm>
Input* Input::instance = nullptr;

void Input::Listen()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			quit = true;
		}
	}

	memcpy(lastFrameKeys, currentFrameKeys, sizeof(Uint8) * SDL_NUM_SCANCODES);
	memcpy(currentFrameKeys, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}

bool Input::isKeyDown(SDL_Scancode scancode)
{
	if (lastFrameKeys[scancode] == false && currentFrameKeys[scancode] == true)
		return true;
	return false;
}

bool Input::isKeyHeld(SDL_Scancode scancode)
{
	if (lastFrameKeys[scancode] == true && currentFrameKeys[scancode] == true)
		return true;
	return false;
}

bool Input::isKeyUp(SDL_Scancode scancode)
{
	if (lastFrameKeys[scancode] == true && currentFrameKeys[scancode] == false)
		return true;
	return false;
}

Input::Input()
{
	for (int i = 0; i <= SDL_NUM_SCANCODES; i++)
	{
		lastFrameKeys[i] = 0;
	}
	memcpy(currentFrameKeys, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}
