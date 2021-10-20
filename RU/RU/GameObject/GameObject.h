#pragma once
class GameObject
{
public:
	GameObject() {};

	virtual void Update(float DeltaTime) = 0;

	virtual void Draw() = 0;


};

