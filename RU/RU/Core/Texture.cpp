#include "Texture.h"
#include "Renderer.h"
#include <iostream>
Texture::Texture()
	:texture(nullptr), width(0), height(0)
{
	std::cout << "calling tex def" << std::endl;
	texture = Renderer::Get()->LoadTexture("C:/Dev/RU/RU/GFX/DefaultTexture.png");
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

Texture::Texture(const char* filePath)
	:texture(nullptr), width(0), height(0)
{
	std::cout << filePath << std::endl;
	texture = Renderer::Get()->LoadTexture(filePath);
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Texture::SetBlendMode(SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode(texture, blendMode);
}

void Texture::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(texture, alpha);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}
