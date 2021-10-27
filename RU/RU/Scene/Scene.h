#pragma once
#include <vector>
#include <memory>
#include "../GameObject/GameObject.h"
#include "../Physics/PhysicsWorld.h"
#include "../Core/Camera.h"
class Scene
{
public:
	Scene(std::shared_ptr<Camera> cam) { camera = cam; }

	std::vector<std::shared_ptr<GameObject>> vecGameObjects;

	void Update(float deltaTime);

	void Draw();

	std::shared_ptr<Camera> camera;

	
};

