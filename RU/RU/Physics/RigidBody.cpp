#include "RigidBody.h"
#include "PhysicsWorld.h"
#include <iostream>
RigidBody::RigidBody()
	:position({ 320, 240 }), velocity({ 500, 0 }), acceleration({ 0, 0 }), halfExtent(32), angle(0), isStatic(false), bounciness(1)
{
	PhysicsWorld::Get()->PushBodyToWorld(std::shared_ptr<RigidBody>(this));
	Vector2 a = { -halfExtent, - halfExtent };
	pointsInBody.emplace_back(a);
	Vector2 b = { halfExtent, -halfExtent };
	pointsInBody.emplace_back(b);
	Vector2 c = { halfExtent, halfExtent };
	pointsInBody.emplace_back(c);
	Vector2 d = { -halfExtent, halfExtent };
	pointsInBody.emplace_back(d);

	Vector2 a1 = { -halfExtent, -halfExtent };
	pointsInBodyTransformed.emplace_back(a);
	Vector2 b1 = { halfExtent, halfExtent };
	pointsInBodyTransformed.emplace_back(b);
	Vector2 c1 = { halfExtent, halfExtent };
	pointsInBodyTransformed.emplace_back(c);
	Vector2 d1 = { -halfExtent, halfExtent };
	pointsInBodyTransformed.emplace_back(d);

	mass = halfExtent * 5;

}

RigidBody::RigidBody(float he)
	: position({ 320, 240 }), velocity({ 500, 0 }), acceleration({ 0, 0 }), halfExtent(he), angle(0), isStatic(false), bounciness(1)
{
	PhysicsWorld::Get()->PushBodyToWorld(std::shared_ptr<RigidBody>(this));
	Vector2 a = { -halfExtent, -halfExtent };
	pointsInBody.emplace_back(a);
	Vector2 b = { halfExtent, -halfExtent };
	pointsInBody.emplace_back(b);
	Vector2 c = { halfExtent, halfExtent };
	pointsInBody.emplace_back(c);
	Vector2 d = { -halfExtent, halfExtent };
	pointsInBody.emplace_back(d);

	Vector2 a1 = {-halfExtent, - halfExtent };
	pointsInBodyTransformed.emplace_back(a);
	Vector2 b1 = { halfExtent, halfExtent };
	pointsInBodyTransformed.emplace_back(b);
	Vector2 c1 = { halfExtent, halfExtent };
	pointsInBodyTransformed.emplace_back(c);
	Vector2 d1 = { -halfExtent, halfExtent };
	pointsInBodyTransformed.emplace_back(d);

	mass = halfExtent * 5;
}

void RigidBody::Update(float deltaTime)
{
	Vector2 drag = (velocity * -1) * 0.8f;
	Vector2 gravity = { 0, 100 };
	Vector2 Initial = { 50, 0 };
	acceleration = gravity + drag;

	if (velocity.Mag() < 0.1)
	{
		velocity = { 0, 0 };
	}

	
	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;
	velocity.Normalize();
	angle = atan2f(velocity.y, velocity.x);
	//angle = 0;
	float radAngle = angle;

	for (int i = 0; i < pointsInBodyTransformed.size(); i++)
	{
		Vector2 a = { 0, 0 };
		a.x = (pointsInBody[i].x * cosf(radAngle)) - (pointsInBody[i].y * sinf(radAngle)) + position.x;
		a.y = (pointsInBody[i].x * sinf(radAngle)) + (pointsInBody[i].y * cosf(radAngle)) + position.y;
		pointsInBodyTransformed[i] = a;
	}
	

	
}
