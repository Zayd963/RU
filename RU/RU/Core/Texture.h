#pragma once
#include <SDL.h>
class Texture
{
public:
	Texture();
	Texture(const char* filePath);

	void SetBlendMode(SDL_BlendMode blendMode);
	void SetAlpha(Uint8 alpha);
	SDL_Texture* GetTexture() { return texture; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

	~Texture();
private:
	SDL_Texture* texture;
	int width;
	int height;
};

