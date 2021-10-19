#include <iostream>
#include <SDL.h>
#include "RU/Core/Engine.h"
int main(int argc, char* argv[])
{


	if (!Engine::Get()->Init())
		return 1;

	Engine::Get()->Run();

	SDL_Quit();
	return 0;
}