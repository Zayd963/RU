#pragma once
#include <vector>
#include <memory>
#include "../GameObject/GameObject.h"
#include "../Physics/PhysicsWorld.h"
class Scene
{
public:
	Scene() {};

	std::vector<std::shared_ptr<GameObject>> vecGameObjects;

	void Update(float deltaTime);

	void Draw();
};

