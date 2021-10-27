#include "PhysicsWorld.h"
#include "../Core/Camera.h"
#include <iostream>
PhysicsWorld* PhysicsWorld::instance = nullptr;

void PhysicsWorld::Update(float deltaTime)
{
	vecCollidingBodies.clear();
	for (int i = 0; i < vecRigidbody.size(); i++)
	{
		for (int j = 1 + i; j < vecRigidbody.size(); j++)
		{
			if (StaticCollision(vecRigidbody[i], vecRigidbody[j]))
			{
				vecCollidingBodies.push_back({ vecRigidbody[i] , vecRigidbody[j] });
			}
		}
	}

	DynamicResponse();
	

	for (auto body : vecRigidbody)
	{
		body->Update(deltaTime);
	}
}

bool PhysicsWorld::StaticCollision(std::shared_ptr<RigidBody> _body1, std::shared_ptr<RigidBody> _body2)
{
	std::shared_ptr<RigidBody> body1 = _body1;
	std::shared_ptr<RigidBody> body2 = _body2;

	float overlap = INFINITY;

	for (int bodyIndex = 0; bodyIndex < 2; bodyIndex++)
	{
		if (bodyIndex == 1)
		{
			body1 = _body2;
			body2 = _body1;
		}

		for (int a = 0; a < body1->pointsInBodyTransformed.size(); a++)
		{
			int b = (a + 1) % body1->pointsInBodyTransformed.size();
			Vector2 axisProj = { -(body1->pointsInBodyTransformed[b].y - body1->pointsInBodyTransformed[a].y), body1->pointsInBodyTransformed[b].x - body1->pointsInBodyTransformed[a].x };
			
			axisProj = axisProj.Normalize();

		

			// Work out min and max 1D points for r1
			float minBody1 = INFINITY, maxBody1 = -INFINITY;
			for (int p = 0; p < body1->pointsInBodyTransformed.size(); p++)
			{
				float q = (body1->pointsInBodyTransformed[p].x * axisProj.x + body1->pointsInBodyTransformed[p].y * axisProj.y);
				minBody1 = std::min(minBody1, q);
				maxBody1 = std::max(maxBody1, q);
			}

			// Work out min and max 1D points for r2
			float minBody2 = INFINITY, maxBody2 = -INFINITY;
			for (int p = 0; p < body2->pointsInBodyTransformed.size(); p++)
			{
				float q = (body2->pointsInBodyTransformed[p].x * axisProj.x + body2->pointsInBodyTransformed[p].y * axisProj.y);
				minBody2 = std::min(minBody2, q);
				maxBody2 = std::max(maxBody2, q);
			}

			overlap = std::min(std::min(maxBody1, maxBody2) - std::max(minBody1, minBody2), overlap);

			if (!(maxBody2 >= minBody1 && maxBody1 >= minBody2))
				return false;
		}
	}
	Vector2 normal = _body2->position - _body1->position;
	Vector2 normalNormalized = normal.Normalize();
	_body1->position -= normalNormalized * overlap;
	return true;
}

void PhysicsWorld::DynamicResponse()
{
	for (auto pair : vecCollidingBodies)
	{
		std::shared_ptr<RigidBody> body1 = pair.first;
		std::shared_ptr<RigidBody> body2 = pair.second;

		//Vector Between Entitys (ie normal)
		Vector2 normal = (body2->position - body1->position).Normalize();
		//Normal of normal (ie tangent)
		Vector2 tangent = { -normal.y, normal.x };
		//Dot product along tangent for ent1
		float dotProductTangent1 = body1->velocity.x * tangent.x + body1->velocity.y * tangent.y;
		//Dot product along tangent for ent2
		float dotProductTangent2 = body2->velocity.x * tangent.x + body2->velocity.y * tangent.y;

		// Dot Product along normal for ent1
		float dotProductNormal1 = body1->velocity.x * normal.x + body1->velocity.y * normal.y;
		// Dot Product along normal for ent2
		float dotProductNormal2 = body2->velocity.x * normal.x + body2->velocity.y * normal.y;

		// Conservation of momentum for ent1
		float momentum1 = (dotProductNormal1 * (body1->mass - body2->mass) + 2.0f * body2->mass * dotProductNormal2) / (body1->mass + body2->mass);
		// Conservation of momentum for ent2
		float momentum2 = (dotProductNormal2 * (body2->mass - body1->mass) + 2.0f * body1->mass * dotProductNormal1) / (body1->mass + body2->mass);

		// Update ent velocities
		body1->velocity = (tangent * dotProductTangent1) + (normal * momentum1);
		body2->velocity = (tangent * dotProductTangent2) + (normal * momentum2);
	}
	
}
