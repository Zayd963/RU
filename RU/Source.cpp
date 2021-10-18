#include <iostream>
#include <SDL.h>
#include "RU/Engine.h"
int main(int argc, char* argv[])
{
	std::cout << "Hello World" << std::endl;

	if (!Engine::Get()->Init())
		return 1;
	Engine::Get()->Run();

	return 0;
}