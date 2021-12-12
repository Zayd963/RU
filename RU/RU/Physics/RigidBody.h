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
	float bounciness;
	bool isStatic;
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	Vector2 acceleration{ 0, 0 };
	std::vector<Vector2> pointsInBody;
	std::vector<Vector2> pointsInBodyTransformed;
};

