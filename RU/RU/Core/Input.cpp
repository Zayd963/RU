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
	lastMouseButton = currentMouseButtons;
	currentMouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
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

bool Input::isKey(SDL_Scancode scancode)
{
	if (lastFrameKeys[scancode] == false && currentFrameKeys[scancode] == true || lastFrameKeys[scancode] == true && currentFrameKeys[scancode] == true)
		return true;
}

int Input::GetMouseX()
{
	return mouseX;
}

int Input::GetMouseY()
{
	return mouseY;
}

Vector2 Input::GetMousePosition()
{
	return Vector2((float)mouseX, (float)mouseY);
}

bool Input::isMouseDown(Uint32 button)
{
	return (!(lastMouseButton & button) && (currentMouseButtons & button));
}

bool Input::isMouseHeld(Uint32 button)
{
	return ((lastMouseButton & button) && (currentMouseButtons & button));
}

bool Input::isMouseUp(Uint32 button)
{
	return ((lastMouseButton & button) && ((currentMouseButtons & button) == 0));
}

bool Input::isMouse(Uint32 button)
{
	return (!(lastMouseButton & button) && (currentMouseButtons & button)) || 
		((lastMouseButton & button) && (currentMouseButtons & button));
}

Input::Input()
{
	for (int i = 0; i <= SDL_NUM_SCANCODES - 1; i++)
	{
		lastFrameKeys[i] = 0;
	}
	memcpy(currentFrameKeys, SDL_GetKeyboardState(NULL), sizeof(Uint8) * SDL_NUM_SCANCODES);
}
