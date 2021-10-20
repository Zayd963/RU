#include "Engine.h"
#include "Renderer.h"
#include "Input.h"
#include "../Scene/Scene.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/DynamicGameObject.h"
#include <memory>
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
	Scene scene;

	std::shared_ptr<DynamicGameObject> obj = std::make_shared<DynamicGameObject>();
	scene.vecGameObjects.emplace_back(obj);

	while (isRunning)
	{
		Input::Get()->Listen();
		isRunning = !Input::Get()->quit;
		ts.SetDeltaTime();


		scene.Update(ts.GetDeltaTime());

		Renderer::Get()->ClearScreen();
		scene.Draw();
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
