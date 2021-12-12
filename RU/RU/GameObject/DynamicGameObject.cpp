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
	scale = 0;
	body = std::make_shared<RigidBody>(scale / 2);
	dstRect.x = (int)body->position.x;
	dstRect.y = (int)body->position.y;
	dstRect.w = scale;
	dstRect.h = scale;
}

DynamicGameObject::DynamicGameObject(const char* filepath)
{
	texture = std::make_shared<Texture>(filepath);
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = texture->GetWidth();
	srcRect.h = texture->GetHeight();
	scale = 64;
	body = std::make_shared<RigidBody>(scale / 2);
	dstRect.x = (int)body->position.x;
	dstRect.y = (int)body->position.y;
	dstRect.w = scale;
	dstRect.h = scale;
}

DynamicGameObject::DynamicGameObject(const char* filepath, float _scale)
{
	texture = std::make_shared<Texture>(filepath);
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = texture->GetWidth();
	srcRect.h = texture->GetHeight();
	scale = _scale;
	body = std::make_shared<RigidBody>(scale / 2);
	dstRect.x = (int)body->position.x;
	dstRect.y = (int)body->position.y;
	dstRect.w = scale;
	dstRect.h = scale;
}

void DynamicGameObject::Update(float deltaTime)
{
	
	Vector2 startMousePos = { 0, 0 };
	SDL_Point mousePoint = { Input::Get()->GetMousePosition().x, Input::Get()->GetMousePosition().y };
	if (SDL_PointInRect(&mousePoint, &dstRect) && Input::Get()->isMouseDown(SDL_BUTTON_LEFT))
	{
		selected = true;
		body->velocity = {0, 0};
	}
	if (Input::Get()->isMouseUp(SDL_BUTTON_LEFT) && selected)
	{
		body->velocity = (body->position - camera->ScreenToWorld(Input::Get()->GetMousePosition())) * 5;
		selected = false;
	}
}

void DynamicGameObject::Draw(std::shared_ptr<Camera> cam)
{

	dstRect.x = (body->position.x - body->halfExtent - cam->offset.x) * cam->scale.x;
	dstRect.y = (body->position.y - body->halfExtent - cam->offset.y) * cam->scale.y;
	
	dstRect.w = scale * cam->scale.x;
	dstRect.h = scale * cam->scale.y;

	

	std::cout << dstRect.y << std::endl;
	Renderer::Get()->Render(texture->GetTexture(), srcRect, dstRect, body->angle * (180 / 3.14), SDL_FLIP_NONE);
	SDL_SetRenderDrawColor(Renderer::Get()->GetRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
	
	

	for (int i = 0; i < body->pointsInBodyTransformed.size(); i++)
	{
		SDL_RenderDrawLine(Renderer::Get()->GetRenderer(), (body->pointsInBodyTransformed[i].x - cam->offset.x) * cam->scale.x,
			(body->pointsInBodyTransformed[i].y - cam->offset.y) * cam->scale.y,
			(body->pointsInBodyTransformed[(i + 1) % body->pointsInBodyTransformed.size()].x - cam->offset.x) * cam->scale.x,
			(body->pointsInBodyTransformed[(i + 1) % body->pointsInBodyTransformed.size()].y - cam->offset.y) * cam->scale.y);
	}

	if (selected)
	{
		Vector2 mousePos = { 0, 0 };
		mousePos = cam->ScreenToWorld(Input::Get()->GetMousePosition());
		SDL_RenderDrawLine(Renderer::Get()->GetRenderer(), (body->position.x - cam->offset.x) * cam->scale.x, (body->position.y - cam->offset.y) * cam->scale.y,
			(mousePos.x - cam->offset.x) * cam->scale.x, (mousePos.y - cam->offset.y) * cam->scale.y);
	}
	
	
	
		

	SDL_SetRenderDrawColor(Renderer::Get()->GetRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
}
