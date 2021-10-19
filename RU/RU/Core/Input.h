#pragma once
#include <SDL.h>
class Input
{
public:
	static Input* Get() { return instance = (instance != nullptr) ? instance : new Input(); }
	void Listen();
	bool isKeyDown(SDL_Scancode scancode);
	bool isKeyHeld(SDL_Scancode scancode);
	bool isKeyUp(SDL_Scancode scancode);
	bool quit = false;
protected:
	Input();

private:
	static Input* instance;
	Uint8 lastFrameKeys[SDL_NUM_SCANCODES];
	Uint8 currentFrameKeys[SDL_NUM_SCANCODES];
	
};