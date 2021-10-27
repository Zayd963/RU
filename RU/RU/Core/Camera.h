#pragma once
#include "../Math/Vector2.h"
class Camera
{
public:
	Camera();

	void Update(float deltaTime);

	void ZoomIn();
	void ZoomOut();

	Vector2 ScreenToWorld(Vector2 pos);
	Vector2 WorldToScreen(Vector2 pos);
	Vector2 startPan = { 0, 0 };
	Vector2 offset;
	Vector2 scale;
};

