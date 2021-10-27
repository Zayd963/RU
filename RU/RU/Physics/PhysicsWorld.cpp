#include "PhysicsWorld.h"
#include "../Core/Camera.h"
#include <iostream>
PhysicsWorld* PhysicsWorld::instance = nullptr;

void PhysicsWorld::Update(float deltaTime)
{
	
	for (auto body1 : vecRigidbody)
	{
		for (auto body2 : vecRigidbody)
		{
			StaticCollision(body1, body2);
		}
	}
}

void PhysicsWorld::StaticCollision(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2)
{
	std::shared_ptr<RigidBody> body = body1;
	std::shared_ptr<RigidBody> target = body2;
	for (int bodyIndex = 0; bodyIndex < 2; bodyIndex++)
	{
		if (bodyIndex == 1)
		{
			body = body2;
			target = body1;
		}

		
		for (int p = 0; p < body->pointsInBodyTransformed.size(); p++)
		{
			Vector2 bodyDiagStart = body->position;
			Vector2 bodyDiagEnd = body->pointsInBodyTransformed[p];

			Vector2 displacement = { 0,0 };
			
			for (int q = 0; q < target->pointsInBodyTransformed.size(); q++)
			{
				Vector2 targetEdgeStart = target->pointsInBodyTransformed[q];
				Vector2 targetEdgeEnd = target->pointsInBodyTransformed[(q + 1) % target->pointsInBodyTransformed.size()];

				
				float h = (targetEdgeEnd.x - targetEdgeStart.x) * (bodyDiagStart.y - bodyDiagEnd.y) - (bodyDiagStart.x - bodyDiagEnd.x) * (targetEdgeEnd.y - targetEdgeStart.y);
				float t1 = ((targetEdgeStart.y - targetEdgeEnd.y) * (bodyDiagStart.x - targetEdgeStart.x) + (targetEdgeEnd.x - targetEdgeStart.x) * (bodyDiagStart.y - targetEdgeStart.y)) / h;
				float t2 = ((bodyDiagStart.y - bodyDiagEnd.y) * (bodyDiagStart.x - targetEdgeStart.x) + (bodyDiagEnd.x - bodyDiagStart.x) * (bodyDiagStart.y - targetEdgeStart.y)) / h;

				if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
				{
					displacement.x += (1.0f - t1) * (bodyDiagEnd.x - bodyDiagStart.x);
					displacement.y += (1.0f - t1) * (bodyDiagEnd.y - bodyDiagStart.y);
				}
			}
			body1->position.x += displacement.x * (bodyIndex == 0 ? -1 : +1);
			body1->position.y += displacement.y * (bodyIndex == 0 ? -1 : +1);
		}
	}

	
	
}
