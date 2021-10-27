#pragma once
#include <vector>
#include "RigidBody.h"
#include <memory>
class PhysicsWorld
{
public:
	static PhysicsWorld* Get() { return instance = (instance != nullptr) ? instance : new PhysicsWorld(); }

	void PushBodyToWorld(std::shared_ptr<RigidBody> rb) { vecRigidbody.emplace_back(rb); }

	void Update(float deltaTime);
	
	bool StaticCollision(std::shared_ptr<RigidBody> r1, std::shared_ptr<RigidBody> r2);
	void DynamicResponse();
	std::vector<std::shared_ptr<RigidBody>> vecRigidbody;
	std::vector<std::pair<std::shared_ptr<RigidBody>, std::shared_ptr<RigidBody>>> vecCollidingBodies;
	bool isCollision = false;
protected:
	PhysicsWorld() {};

	

private:
	static PhysicsWorld* instance;
	
};

