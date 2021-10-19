#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Timer.h"
class Engine
{
public:
	static Engine* Get() { return instance = (instance != nullptr) ? instance : instance = new Engine(); }
	bool Init();
	bool Run();

	~Engine();
protected:
	Engine();

private:
	static Engine* instance;
	bool isRunning = true;
};

