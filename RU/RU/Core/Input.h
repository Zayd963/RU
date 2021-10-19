#pragma once
#include <SDL.h>
#include "../Math/Vector2.h"
class Input
{
public:
	static Input* Get() { return instance = (instance != nullptr) ? instance : new Input(); }
	void Listen();
	bool isKeyDown(SDL_Scancode scancode);
	bool isKeyHeld(SDL_Scancode scancode);
	bool isKeyUp(SDL_Scancode scancode);
	int GetMouseX();
	int GetMouseY();
	Vector2 GetMousePosition();
	bool isMouseDown(Uint32 button);
	bool isMouseHeld(Uint32 button);
	bool isMouseUp(Uint32 button);

	bool quit = false;
protected:
	Input();

private:
	static Input* instance;
	Uint8 lastFrameKeys[SDL_NUM_SCANCODES];
	Uint8 currentFrameKeys[SDL_NUM_SCANCODES];
	Uint32 currentMouseButtons = 0;
	Uint32 lastMouseButton = 0;
	int mouseX = 0;
	int mouseY = 0;
	
};