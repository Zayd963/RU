#include "Scene.h"

void Scene::Update(float deltaTime)
{
	for(auto gameObject : vecGameObjects)
	{
		gameObject->Update(deltaTime);
	}
}

void Scene::Draw()
{
	for (auto gameObject : vecGameObjects)
	{
		gameObject->Draw();
	}
}
