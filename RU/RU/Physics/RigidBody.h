#pragma once
#include "../Math/Vector2.h"
#include <vector>
class RigidBody
{
public:
	RigidBody();
	RigidBody(float he);

	void Update(float deltaTime);

	float halfExtent;
	float angle;
	float mass;
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	std::vector<Vector2> pointsInBody;
	std::vector<Vector2> pointsInBodyTransformed;
};

