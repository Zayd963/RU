#include <iostream>
#include <SDL.h>
#include "src/Engine.h"
int main(int argc, char* argv[])
{
	std::cout << "Hello World" << std::endl;

	if (!Engine::Get()->Init())
		return 1;
	Engine::Get()->Run();

	return 0;
}