#include "Engine.h"
#include "Renderer.h"

Engine* Engine::instance = nullptr;

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL Failed to init" << std::endl;
		return false;
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "IMG Failed To Init" << std::endl;
		return false;
	}

	return true;
}

bool Engine::Run()
{
	Timer ts;
	
	while (isRunning)
	{
		ts.SetDeltaTime();
		Renderer::Get()->Display();
	}

	return true;
}


Engine::~Engine()
{
}

Engine::Engine()
{
}
