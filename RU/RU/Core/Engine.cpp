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
	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	Scene scene(camera);

	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<DynamicGameObject> temp = std::make_shared<DynamicGameObject>("C:/Dev/RU/RU/GFX/DefaultTexture.png");
		temp->GetRigidbody()->position.x = i * 500;
		temp->GetRigidbody()->position.y = 0;
		temp->camera = camera;
		scene.vecGameObjects.emplace_back(temp);
	}

	std::shared_ptr<DynamicGameObject> player = std::make_shared<DynamicGameObject>("C:/Dev/RU/RU/GFX/Tex.png", 128);
	player->GetRigidbody()->position.x = 368;
	player->GetRigidbody()->position.y = 320;
	player->camera = camera;
	scene.vecGameObjects.push_back(player);

	while (isRunning)
	{
		Input::Get()->Listen();
		isRunning = !Input::Get()->quit;
		ts.SetDeltaTime();

		Vector2 vec = Input::Get()->GetMousePosition();

		scene.Update(ts.GetDeltaTime());

		//std::cout << player->GetRigidbody()->position.x << " " << player->GetRigidbody()->position.y << std::endl;
		//std::cout << PhysicsWorld::Get()->vecCollidingBodies.size() << std::endl;
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
