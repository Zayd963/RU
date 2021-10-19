#include "Engine.h"
#include "Renderer.h"
#include "Input.h"
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
		Input::Get()->Listen();

		isRunning = !Input::Get()->quit;

		if (Input::Get()->isKeyDown(SDL_SCANCODE_SPACE))
		{
			std::cout << "Space pressed" << std::endl;
		}

		if (Input::Get()->isKeyHeld(SDL_SCANCODE_SPACE))
		{
			std::cout << "Space Held" << std::endl;
		}

		if (Input::Get()->isKeyUp(SDL_SCANCODE_SPACE))
		{
			std::cout << "Space Up" << std::endl;
		}

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
