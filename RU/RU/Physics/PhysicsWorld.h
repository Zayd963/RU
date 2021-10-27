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
	
	void StaticCollision(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2);
	std::vector<std::shared_ptr<RigidBody>> vecRigidbody;
protected:
	PhysicsWorld() {};

	

private:
	static PhysicsWorld* instance;
	
};

