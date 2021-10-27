#pragma once
#include "../Core/Camera.h"
#include <memory>
class GameObject
{
public:
	GameObject() {};

	virtual void Update(float DeltaTime) = 0;

	virtual void Draw(std::shared_ptr<Camera> cam) = 0;


};

