#include "RigidBody.h"
#include "PhysicsWorld.h"
RigidBody::RigidBody()
	:position({ 320, 240 }), velocity({ 0, 0 }), acceleration({ 0, 0 }), halfExtent(32), angle(0)
{
	PhysicsWorld::Get()->PushBodyToWorld(this);
}

RigidBody::RigidBody(float he)
	: position({ 320, 240 }), velocity({ 0, 0 }), acceleration({ 0, 0 }), halfExtent(he)
{

}

void RigidBody::Update(float deltaTime)
{
	/*Vector2 drag = (velocity * -1) * 0.8f;
	Vector2 gravity = { 0, 100 };
	acceleration = gravity + drag;*/

	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;
}
