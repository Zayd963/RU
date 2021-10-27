#include "DynamicGameObject.h"
#include "../Core/Renderer.h"
#include "../Core/Input.h"
#include "../Scene/Scene.h"
#include <iostream>
DynamicGameObject::DynamicGameObject()
{
	texture = std::make_shared<Texture>();
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = texture->GetWidth();
	srcRect.h = texture->GetHeight();
	body = std::make_shared<RigidBody>(32.f);
	dstRect.x = (int)body->position.x;
	dstRect.y = (int)body->position.y;
	dstRect.w = 64;
	dstRect.h = 64;
}

DynamicGameObject::DynamicGameObject(const char* filepath)
{
	texture = std::make_shared<Texture>(filepath);
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = texture->GetWidth();
	srcRect.h = texture->GetHeight();
	body = std::make_shared<RigidBody>(32.f);
	dstRect.x = (int)body->position.x;
	dstRect.y = (int)body->position.y;
	dstRect.w = 64;
	dstRect.h = 64;
}

void DynamicGameObject::Update(float deltaTime)
{
	

	body->Update(deltaTime);
}

void DynamicGameObject::Draw(std::shared_ptr<Camera> cam)
{

	dstRect.x = (body->position.x - body->halfExtent - cam->offset.x) * cam->scale.x;
	dstRect.y = (body->position.y - body->halfExtent - cam->offset.y) * cam->scale.y;
	
	dstRect.w = 64 * cam->scale.x;
	dstRect.h = 64 * cam->scale.y;

	SDL_Point mousePoint = { Input::Get()->GetMousePosition().x, Input::Get()->GetMousePosition().y };
	if (SDL_PointInRect(&mousePoint, &dstRect) && Input::Get()->isMouse(SDL_BUTTON_LEFT))
	{
		body->position = cam->ScreenToWorld(Input::Get()->GetMousePosition());
	}

	Renderer::Get()->Render(texture->GetTexture(), srcRect, dstRect, body->angle, SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(Renderer::Get()->GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	
	

	for (int i = 0; i < body->pointsInBodyTransformed.size(); i++)
	{
		SDL_RenderDrawLine(Renderer::Get()->GetRenderer(), (body->pointsInBodyTransformed[i].x - cam->offset.x) * cam->scale.x,
			(body->pointsInBodyTransformed[i].y - cam->offset.y) * cam->scale.y,
			(body->pointsInBodyTransformed[(i + 1) % body->pointsInBodyTransformed.size()].x - cam->offset.x) * cam->scale.x,
			(body->pointsInBodyTransformed[(i + 1) % body->pointsInBodyTransformed.size()].y - cam->offset.y) * cam->scale.y);
	}
	
	
	
		

	SDL_SetRenderDrawColor(Renderer::Get()->GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
}
