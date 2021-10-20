#include "DynamicGameObject.h"
#include "../Core/Renderer.h"
#include <iostream>
DynamicGameObject::DynamicGameObject()
	:texture(nullptr)
{
	texture = Renderer::Get()->LoadTexture("C:/Dev/RU/RU/GFX/DefaultTexture.png");
	position = { 320, 240 };
	dstRect.x = (int)position.x;
	dstRect.y = (int)position.y;
	dstRect.w = 64;
	dstRect.h = 64;
}

void DynamicGameObject::Update(float deltaTime)
{
	position.x += 20 * deltaTime;
	dstRect.x = (int)position.x;
}

void DynamicGameObject::Draw()
{
	Renderer::Get()->Render(texture, { 0, 0, 32, 32 }, dstRect);
}
