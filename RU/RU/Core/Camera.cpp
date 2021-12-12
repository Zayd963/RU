#include "Camera.h"
#include "Input.h"
#include "Renderer.h"
#include <iostream>
Camera::Camera()
	:offset({ 0, 0 }), scale({1, 1})
{
	offset = { -320, -240 };
}

void Camera::Update(float deltaTime)
{
	Vector2 mousePos = Input::Get()->GetMousePosition();
	

	if (Input::Get()->isMouseDown(SDL_BUTTON_RMASK))
	{
		startPan = mousePos;
	}
	if (Input::Get()->isMouseHeld(SDL_BUTTON_RMASK))
	{
		offset -= (mousePos - startPan) / scale.x;

		startPan = mousePos;
	}

	Vector2 mousePosBeforeZoom = ScreenToWorld(mousePos);

	if (Input::Get()->isKey(SDL_SCANCODE_Q))
	{
		ZoomIn();
	}

	if (Input::Get()->isKey(SDL_SCANCODE_E))
	{
		ZoomOut();
	}
	
	Vector2 mousePosAfterZoom = ScreenToWorld(mousePos);
	offset += (mousePosBeforeZoom - mousePosAfterZoom);
}

void Camera::ZoomIn()
{
	scale.x *= 1.001f;
	scale.y *= 1.001f;
}

void Camera::ZoomOut()
{
	scale.x *= 0.999f;
	scale.y *= 0.999f;
}

Vector2 Camera::ScreenToWorld(Vector2 pos)
{
	return Vector2((pos.x / scale.x) + offset.x, (pos.y / scale.y) + offset.y);
}

Vector2 Camera::WorldToScreen(Vector2 pos)
{
	return Vector2((pos.x - offset.x) * scale.x, (pos.y - offset.y) * scale.y);
}
