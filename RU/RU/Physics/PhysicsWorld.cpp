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
	//StaticCollision();

	std::cout << isCollision << std::endl;

	DynamicResponse();
	

	for (auto body : vecRigidbody)
	{
		body->Update(deltaTime);
	}
}

bool PhysicsWorld::StaticCollision(std::shared_ptr<RigidBody> r1, std::shared_ptr<RigidBody> r2)
{
	std::shared_ptr<RigidBody> poly1 = r1;
	std::shared_ptr<RigidBody> poly2 = r2;

	float overlap = INFINITY;

	for (int shape = 0; shape < 2; shape++)
	{
		if (shape == 1)
		{
			poly1 = r2;
			poly2 = r1;
		}

		for (int a = 0; a < poly1->pointsInBodyTransformed.size(); a++)
		{
			int b = (a + 1) % poly1->pointsInBodyTransformed.size();
			Vector2 axisProj = { -(poly1->pointsInBodyTransformed[b].y - poly1->pointsInBodyTransformed[a].y), poly1->pointsInBodyTransformed[b].x - poly1->pointsInBodyTransformed[a].x };
			float d = sqrtf(axisProj.x * axisProj.x + axisProj.y * axisProj.y);
			axisProj = { axisProj.x / d, axisProj.y / d };

			// Work out min and max 1D points for r1
			float min_r1 = INFINITY, max_r1 = -INFINITY;
			for (int p = 0; p < poly1->pointsInBodyTransformed.size(); p++)
			{
				float q = (poly1->pointsInBodyTransformed[p].x * axisProj.x + poly1->pointsInBodyTransformed[p].y * axisProj.y);
				min_r1 = std::min(min_r1, q);
				max_r1 = std::max(max_r1, q);
			}

			// Work out min and max 1D points for r2
			float min_r2 = INFINITY, max_r2 = -INFINITY;
			for (int p = 0; p < poly2->pointsInBodyTransformed.size(); p++)
			{
				float q = (poly2->pointsInBodyTransformed[p].x * axisProj.x + poly2->pointsInBodyTransformed[p].y * axisProj.y);
				min_r2 = std::min(min_r2, q);
				max_r2 = std::max(max_r2, q);
			}

			overlap = std::min(std::min(max_r1, max_r2) - std::max(min_r1, min_r2), overlap);

			if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
				return false;
		}
	}
	Vector2 d = { r2->position.x - r1->position.x, r2->position.y - r1->position.y };	
	float s = sqrtf(d.x * d.x + d.y * d.y);
	r1->position.x -= overlap * d.x / s;
	r1->position.y -= overlap * d.y / s;
	return true;
}

void PhysicsWorld::DynamicResponse()
{
	for (auto pair : vecCollidingBodies)
	{
		std::shared_ptr<RigidBody> ent1 = pair.first;
		std::shared_ptr<RigidBody> ent2 = pair.second;

		//Vector Between Entitys (ie normal)
		Vector2 normal = (ent2->position - ent1->position).Normalize();
		//Normal of normal (ie tangent)
		Vector2 tangent = { -normal.y, normal.x };
		//Dot product along tangent for ent1
		float dotProductTangent1 = ent1->velocity.x * tangent.x + ent1->velocity.y * tangent.y;
		//Dot product along tangent for ent2
		float dotProductTangent2 = ent2->velocity.x * tangent.x + ent2->velocity.y * tangent.y;

		// Dot Product along normal for ent1
		float dotProductNormal1 = ent1->velocity.x * normal.x + ent1->velocity.y * normal.y;
		// Dot Product along normal for ent2
		float dotProductNormal2 = ent2->velocity.x * normal.x + ent2->velocity.y * normal.y;

		// Conservation of momentum for ent1
		float momentum1 = (dotProductNormal1 * (1 - 1) + 2.0f * 1 * dotProductNormal2) / (1 + 1);
		// Conservation of momentum for ent2
		float momentum2 = (dotProductNormal2 * (1 - 1) + 2.0f * 1 * dotProductNormal1) / (1 + 1);

		// Update ent velocities
		ent1->velocity = (tangent * dotProductTangent1) + (normal * momentum1);
		ent2->velocity = (tangent * dotProductTangent2) + (normal * momentum2);
	}
	
}
