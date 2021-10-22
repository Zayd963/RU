#pragma once
#include "../Math/Vector2.h"
class RigidBody
{
public:
	RigidBody();
	RigidBody(float he);

	void Update(float deltaTime);

	float halfExtent;
	double angle;
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
};

