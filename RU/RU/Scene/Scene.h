#pragma once
#include <vector>
#include <memory>
#include "../GameObject/GameObject.h"

class Scene
{
public:
	Scene() {};

	std::vector<std::shared_ptr<GameObject>> vecGameObjects;

	void Update(float deltaTime);

	void Draw();
};

