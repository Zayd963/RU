#pragma once
#include "GameObject.h"
#include "../Math/Vector2.h"
#include <SDL.h>
class DynamicGameObject : public GameObject
{
public:
	DynamicGameObject();

	void Update(float deltaTime);
	void Draw();

private:
	Vector2 position;
	SDL_Texture* texture;
	SDL_Rect dstRect;
};

