#pragma once
#include "GameObject.h"
#include "../Math/Vector2.h"
#include <SDL.h>
#include "../Physics/RigidBody.h"
#include "../Core/Texture.h"
#include "../Core/Camera.h"
#include <memory>
class DynamicGameObject : public GameObject
{
public:
	DynamicGameObject();
	DynamicGameObject(const char* filepath);

	virtual void Update(float deltaTime) override;
	void Draw(std::shared_ptr<Camera> cam) override;
	std::shared_ptr<RigidBody> GetRigidbody() { return body; }

private:
	std::shared_ptr<RigidBody> body;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
	std::shared_ptr<Texture> texture;
};

