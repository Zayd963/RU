#include "DynamicGameObject.h"
#include "../Core/Renderer.h"
#include "../Core/Input.h"
#include <iostream>
DynamicGameObject::DynamicGameObject()
{
	std::cout << "Default" << std::endl;
	texture = std::make_shared<Texture>();
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = texture->GetWidth();
	srcRect.h = texture->GetHeight();
	body = RigidBody(32.f);
	dstRect.x = (int)body.position.x;
	dstRect.y = (int)body.position.y;
	dstRect.w = 64;
	dstRect.h = 64;
}

DynamicGameObject::DynamicGameObject(const char* filepath)
{
	std::cout << "calling non cins" << std::endl;
	texture = std::make_shared<Texture>(filepath);
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = texture->GetWidth();
	srcRect.h = texture->GetHeight();
	body = RigidBody(32.f);
	dstRect.x = (int)body.position.x;
	dstRect.y = (int)body.position.y;
	dstRect.w = 64;
	dstRect.h = 64;
}

void DynamicGameObject::Update(float deltaTime)
{
	body.Update(deltaTime);
	dstRect.x = body.position.x - body.halfExtent;
	dstRect.y = body.position.y - body.halfExtent;
}

void DynamicGameObject::Draw()
{
	Renderer::Get()->Render(texture->GetTexture(), srcRect, dstRect, body.angle, SDL_FLIP_NONE);
}
