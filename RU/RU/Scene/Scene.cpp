#include "Scene.h"

void Scene::Update(float deltaTime)
{
	camera->Update(deltaTime);

	PhysicsWorld::Get()->Update(deltaTime);

	for(auto gameObject : vecGameObjects)
	{
		gameObject->Update(deltaTime);
	}
}

void Scene::Draw()
{
	for (auto gameObject : vecGameObjects)
	{
		gameObject->Draw(camera);
	}
}
