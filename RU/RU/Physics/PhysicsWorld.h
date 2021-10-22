#pragma once
#include <vector>
#include "RigidBody.h"
class PhysicsWorld
{
public:
	static PhysicsWorld* Get() { return instance = (instance != nullptr) ? instance : new PhysicsWorld(); }

	void PushBodyToWorld(RigidBody* rb) { vecRigidbody.emplace_back(rb); }

	void Update(float deltaTime);
	
	std::vector<RigidBody*> vecRigidbody;
protected:
	PhysicsWorld() {};

	

private:
	static PhysicsWorld* instance;
	
};

